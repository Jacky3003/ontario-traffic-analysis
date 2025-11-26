#include "filemodule.h"

int file_road_size(std::string filename){
    int num_values = 0;
    double target;
    FILE *curr_file;
    curr_file = fopen(filename.c_str(), "r");

    for (; fscanf(curr_file, "%lf", &target) != EOF; num_values++){}
    
    fclose(curr_file);
    return num_values;
}