#include "filemodule.h"

NetFile::NetFile(std::string filename, int block_size){
    // the NC_64BIT_DATA option will work with higher dimensions
    // but may break Pythons NetCDF reading
    handle_err(nc_create(filename.c_str(), NC_CLOBBER, &file_id));
    offset[0] = {0};
    block[0] = {(size_t)block_size};
}

NetFile::NetFile(){}

void NetFile::close(){
    handle_err(nc_close(file_id));
}

void NetFile::define_file(int x, int y){
    int def_dim_id;
    size_t dim = (size_t)x*(size_t)y;
    handle_err(nc_def_dim(file_id, "traffic_density", dim, &def_dim_id));
    dim_id[0] = def_dim_id;
    handle_err(nc_def_var(file_id, "data", NC_DOUBLE, 1, dim_id, &var_id));
    nc_put_att_int(file_id, NC_GLOBAL, "time_steps", NC_INT, 1, &y);
    nc_put_att_int(file_id, NC_GLOBAL, "road_len", NC_INT, 1, &x);
    handle_err(nc_enddef(file_id));
}

void NetFile::write(rarray<double, 1> arr){
    handle_err(nc_put_vara_double(file_id, var_id, offset, block, arr.data()));
    offset[0] += block[0];
}

void NetFile::handle_err(int err){
    if(err != NC_NOERR){
        std::cout << "NetCDF Error: " << nc_strerror(err) << std::endl;
        exit(-1);
    }
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