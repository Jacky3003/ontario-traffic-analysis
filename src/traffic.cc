#include <iostream>
#include <algorithm>

#include "mathfunctions.h"
#include "arrayinit.h"
#include "filemodule.h"

int main(int argc, char *argv[]){

    // parse file path (if given)
    std::string file_path = (argc>1) ? argv[1]:"";

    // basic parameters
    int timesteps = 1000;
    int road_len = (file_path.length() == 0) ? 10: file_road_size(file_path);
    int scaling_factor = 100;
    double x_delta = (double)(1.0/road_len);
    double t_delta = (double)(1.0/timesteps);
    double time_dist_ratio = t_delta/x_delta;
    double max_velocity = 1.0;
    rarray<double, 1> road_vals(road_len);
    rarray<double, 1> new_road_vals(road_len);

    // TODO: MPI parameters

    // initalize values for array at t = 0
    if (file_path.length() == 0)
        arraysin(0, road_len, scaling_factor, x_delta, road_vals);
    else
        arrayfile(road_vals, file_path);

    // get the maximum traffic density based on the array
    // TODO: use MPI reductions to distribute the max element from root
    double max_density = *std::max_element(road_vals.begin(), road_vals.end());

    // TODO: use MPI Scatter to distribute the array amongst local arrays with ghost cells

    for(int t = 0; t < timesteps; t++){
        std::cout << "Timestep " << t << ":" << road_vals << std::endl;
        // TODO: use MPI sends and recieves to update ghost cells

        // TODO: update ghost cell of process 0 and process max_rank to reflect
        // loop around logic for traffic

        // calculate the flux logic into the new cells
        for(int i = 0; i < road_len; i++){

            double k_curr, k_next, k_prev;
            k_curr = road_vals[i];

            if(i >= 1 && i < road_len - 1){
                k_next = road_vals[i+1]; k_prev = road_vals[i-1];
            }
            else if (i == 0){
                k_next = road_vals[i+1]; k_prev = road_vals[road_len-1];
            }
            else if (i == road_len - 1){
                k_next = road_vals[0]; k_prev = road_vals[i-1];
            }

            double f_prev = determine_flux(max_velocity, max_density, k_prev, k_curr);
            double f_curr = determine_flux(max_velocity, max_density, k_curr, k_next);
            new_road_vals[i] = road_vals[i] - (time_dist_ratio)*(f_curr - f_prev);
        }

        // copy new cell values into old cells
        for(int i = 0; i < road_len; i++)
            road_vals[i] = new_road_vals[i];
        
        // write to netCDF
        // TODO: use MPI gather to collect results to consolodate the writing
    }
    // close MPI
    return 0;
}