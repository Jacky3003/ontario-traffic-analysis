#include <iostream>
#include <algorithm>
#include <mpi.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "mathfunctions.h"
#include "arrayinit.h"
#include "filemodule.h"
#include "cliargs.h"

int main(int argc, char *argv[]){

    // parse cli arguments
    CliArgs parser(argc, argv);

    #ifdef _OPENMP
    omp_set_num_threads(parser.threadcount);
    #endif

    // MPI parameters
    int rank;
    int size;
    int process_road_len;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int left = (rank - 1 < 0) ? size - 1 : rank - 1;
    int right = (rank + 1 >= size) ? 0 : rank +1;

    int road_len;
    if (rank == 0){
        road_len = (parser.filepath.length() == 0) ? 1000: file_road_size(parser.filepath);
    }
    MPI_Bcast(&road_len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (road_len % size != 0){
        if (rank == 0)
            std::cerr << "Road length not a multiple of MPI processes, exiting..." << std::endl;
        MPI_Finalize();
        exit(0);
    }

    // parameters per process
    int timesteps = 10000;
    int scaling_factor = 100;
    double x_delta = (double)(1.0/road_len);
    double t_delta = (double)(1.0/timesteps);
    double time_dist_ratio = t_delta/x_delta;
    double max_velocity = 1.0;
    double max_density;
    process_road_len = road_len/size;
    rarray<double, 1> road_vals(road_len);
    rarray<double, 1> new_road_vals(process_road_len + 2);
    rarray<double, 1> process_road_vals(process_road_len + 2);

    // set up dependencies for process 0
    NetFile netcdf_file;
    if (rank == 0){
        netcdf_file = NetFile("results.nc", road_len);
        netcdf_file.define_file(road_len, timesteps + 1);

        // initalize values for array at t = 0
        if (parser.filepath.length() == 0)
            arraysin(0, road_len, scaling_factor, x_delta, road_vals);
        else
            arrayfile(road_vals, parser.filepath);

        // get the maximum traffic density based on the starting array
        max_density = *std::max_element(road_vals.begin(), road_vals.end());

        // inital netCDF write
        netcdf_file.write(road_vals);
    }

    MPI_Bcast(&max_density, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(road_vals.data(), process_road_len, MPI_DOUBLE,
        &process_road_vals.data()[1], process_road_len, MPI_DOUBLE,
        0, MPI_COMM_WORLD);

    for(int t = 0; t < timesteps; t++){

        MPI_Sendrecv(&process_road_vals.data()[1], 1, MPI_DOUBLE, left, 0,
            &process_road_vals.data()[process_road_len+1], 1, MPI_DOUBLE, right, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Sendrecv(&process_road_vals.data()[process_road_len], 1, MPI_DOUBLE, right, 0,
            &process_road_vals.data()[0], 1, MPI_DOUBLE, left, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // calculate the flux logic into the new cells
        #pragma omp parallel for default(none) shared(process_road_len, max_velocity, max_density,\
            time_dist_ratio, new_road_vals, process_road_vals)
        for(int i = 1; i <= process_road_len; i++){

            double k_curr, k_next, k_prev;
            k_curr = process_road_vals[i];
            k_next = process_road_vals[i+1];
            k_prev = process_road_vals[i-1];

            double f_prev = determine_flux(max_velocity, max_density, k_prev, k_curr);
            double f_curr = determine_flux(max_velocity, max_density, k_curr, k_next);
            new_road_vals[i] = process_road_vals[i] - (time_dist_ratio)*(f_curr - f_prev);
        }

        // copy new cell values into old cells
        #pragma omp parallel for default(none) shared(process_road_vals, new_road_vals,\
            process_road_len)
        for(int i = 1; i <= process_road_len; i++)
            process_road_vals[i] = new_road_vals[i];
        
        // gather results and write array to netCDF
        MPI_Gather(&process_road_vals.data()[1], process_road_len, MPI_DOUBLE,
            road_vals.data(), process_road_len, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        if (rank == 0)
            netcdf_file.write(road_vals);
    }

    // close netCDF file
    if (rank == 0)
        netcdf_file.close();
    
    // close MPI
    MPI_Finalize();
    return 0;
}