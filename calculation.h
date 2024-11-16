#ifndef CALCULATION_H
#define CALCULATION_H
#include <math.h>
double func1 (double x, double t)
{
    return cos(t/x) - 2.0 * sin(1/x) + 1.0/x;
}
double func2 (double x, double t)
{
    return sin(log(x)) - cos(log(x)) + t*log(x);
}
#endif
