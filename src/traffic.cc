#include <iostream>

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
    double interval_val = 0.05;
    rarray<double, 1> road_vals(road_len);

    // MPI parameters

    // initalize values for array at t = 0
    if (file_path.length() == 0)
        arraysin(0, road_len, scaling_factor, interval_val, road_vals);
    else
        arrayfile(road_vals, file_path);

    // use MPI Scatter to distribute the array amongst local arrays with ghost cells

    for(int t = 0; t < timesteps; t++){

    }

    std::cout << "Starting project with some sin(x): " << road_vals << std::endl;

    // close MPI
    return 0;
}