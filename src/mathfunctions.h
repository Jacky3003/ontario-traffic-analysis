/**
 * Module to support custom mathematical operations
 * as part of the program.
 */
#include <math.h>

/// @brief function that samples discrete values from
///        asin(x) + a, where a is a scaling factor
///
/// @param  a          scaling factor for the function
/// @param  x          passed in value for x
///
/// @return the calculated value
///
double asinx(double a, double x);