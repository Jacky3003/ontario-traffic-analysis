/**
 * Module containing file libraries that are used for the program
 */

#include <netcdf.h>
#include <netcdf_par.h>
#include <stdio.h>
#include <string>
#include <rarray>
#include <mpi.h>
#ifdef _OPENMP
#include <omp.h>
#endif

/// @class NetFile
/// @brief Wrapper class for NetCDF functionality
/// @note The official docs can be found here for file I/O:
/// https://docs.unidata.ucar.edu/netcdf-c/current/group__datasets.html
///
class NetFile {
    public:
        int file_id;
        int dim_id[1];
        int var_id;

        /// @brief default constructor for non initalized NetCDF class.
        NetFile();

        /// @brief constructor for creating a NetCDF file using this wrapper
        /// @param filename   name of the file to create
        /// @param block_size size of the block to write each time.
        /// @note this function also opens the file as well, so be sure to close when done
        NetFile(std::string filename, int block_size);

        /// @brief closes the NetCDF file
        void close();

        /// @brief defines the file of the netCDF file to write
        ///        this includes defining the dimension, parameters
        ///        and variables
        /// @param x column dimension of the matrix
        /// @param y row dimension of the matrix
        void define_file(int x, int y);

        /// @brief writes an array to the NetCDF file
        /// @param arr the array of doubles to write
        void write(rarray<double, 1> arr, size_t start, size_t count);

        /// @brief handles errors regarding calls to NetCDF
        /// @param err the error to handle
        void handle_err(int err);
};

/// @brief function that finds the number of values in a given
///        .data file.
///
/// @param  filename     name of the given file.
///
/// @return the number of values passed into the .data file
///
int file_road_size(std::string filename);