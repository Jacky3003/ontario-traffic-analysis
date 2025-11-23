/**
 * Module containing file libraries that are used for the program
 */

#include <netcdf.h>
#include <stdio.h>
#include <string>

/// @brief function that finds the number of values in a given
///        .data file.
///
/// @param  filename     name of the given file.
///
/// @return the number of values passed into the .data file
///
int file_road_size(std::string filename);