/**
 * Module for setting up arrays for the project.
 */

#include <rarray>
#include <string>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "mathfunctions.h"

/// @brief function that initalizes an array of values
///        from asin(x) + a, based on a given interval 
///
/// @param  start             starting index of the array
/// @param  end               ending index of the array
/// @param  a                 scaling factor for sin function
/// @param  interval          interval between discrete values
/// @param  x                 the array in this context
///
/// @return the array with new values
///
void arraysin(int start, int end, double a, double interval, rarray<double, 1> &x);

/// @brief function that initalizes an array of values
///        based on a given text file of
///
/// @param  x                 the array in this context
/// @param  filename          name of the file
///
/// @return the array with new values
///
void arrayfile(rarray<double, 1> &x, std::string filename);