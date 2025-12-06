#include "mathfunctions.h"

double asinx(double a, double x){
    return a*sin(x) + a;
}

double flux(double vm, double dm, double kval){
    double first_term = vm*kval;
    double second_term = (vm/dm)*(pow(kval, 2));
    return first_term - second_term;
}

double determine_flux(double vm, double dm, double k, double k_next){
    double res;

    if (k <= k_next)
        res = std::min(flux(vm, dm, k), flux(vm, dm, k_next));
    else
        res = std::max(flux(vm, dm, k), flux(vm, dm, k_next));

    return res;
}