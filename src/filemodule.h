/**
 * Module containing file libraries that are used for the program
 */

#include <netcdf.h>
#include <stdio.h>
#include <string>

/// @class NetFile
/// @brief Wrapper class for NetCDF functionality
/// @note The official docs can be found here for file I/O:
/// https://docs.unidata.ucar.edu/netcdf-c/current/group__datasets.html
///
class NetFile {
    public:
        int file_id;
        int err_status;
        /// @brief constructor for creating a NetCDF file using this wrapper
        /// @param filename name of the file to create
        NetFile(std::string filename);
        /// @brief closes the NetCDF file
        void close();
};

/// @brief function that finds the number of values in a given
///        .data file.
///
/// @param  filename     name of the given file.
///
/// @return the number of values passed into the .data file
///
int file_road_size(std::string filename);