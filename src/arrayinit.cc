#include "arrayinit.h"

void arraysin(int start, int end, double a, double interval, rarray<double, 1> &x){
    for(int i = start; i < end; i++)
        x[i] = asinx(a, interval*(i-1));
}

void arrayfile(rarray<double, 1> &x, std::string filename){
    int target;
    int curr_index = 0;
    FILE *curr_file;
    curr_file = fopen(filename.c_str(), "r");

    for (; fscanf(curr_file, "%d", &target) != EOF; curr_index++){
        x[curr_index] = target;
    }
    
    fclose(curr_file);
}