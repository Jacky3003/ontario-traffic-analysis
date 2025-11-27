#include "filemodule.h"

NetFile::NetFile(std::string filename){
    err_status = 0;
    int nc_err = nc_create(filename.c_str(), NC_CLOBBER, &file_id);
    if (nc_err != NC_NOERR)
        err_status = 1;
}

void NetFile::close(){
    nc_close(file_id);
}

int file_road_size(std::string filename){
    int num_values = 0;
    double target;
    FILE *curr_file;
    curr_file = fopen(filename.c_str(), "r");

    for (; fscanf(curr_file, "%lf", &target) != EOF; num_values++){}
    
    fclose(curr_file);
    return num_values;
}