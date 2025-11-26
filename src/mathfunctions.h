/**
 * Module to support custom mathematical operations
 * as part of the program.
 */
#include <math.h>
#include <algorithm>

/// @brief function that samples discrete values from
///        asin(x) + a, where a is a scaling factor
///
/// @param  a          scaling factor for the function
/// @param  x          passed in value for x
///
/// @return the calculated value
///
double asinx(double a, double x);

/// @brief function that calculates the flux of the current traffic
///        at a given point xval on the 1-D street
///
/// @param  vm          maximum velocity allowed on the traffic
/// @param  dm          maximum density allowed on the traffic
/// @param  kval        given range value based on evolution of differential equation.
///
/// @return the calculated value
///
double flux(double vm, double dm, double xval);

/// @brief function that determines the logic for which flux value to use 
///        durring approximation.
///
/// @param  vm          maximum velocity allowed on the traffic
/// @param  dm          maximum density allowed on the traffic
/// @param  kval_curr           given current domain value
/// @param  kval_next      given next domain value
///
/// @return the calculated value
///
double determine_flux(double vm, double dm, double x, double x_next);