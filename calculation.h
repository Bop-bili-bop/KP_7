#ifndef CALCULATION_H
#define CALCULATION_H
#include <math.h>
double function1 (double x, double t)
{
    return cos(t/x) - 2.0 * sin(1/x) + 1.0/x;
}
double function2 (double x, double t)
{
    return sin(log(x)) - cos(log(x)) + t*log(x);
}
double half_division_method(double a, double b, double t, double epsilon, double x, double (*function)(double, double))
{
    double delta = 0;
    double product = 0;
    int has_solution = 0;
    do
    {
        x = (a + b) / 2.0;
        delta = fabs(b - a);
        product = function(a, t) * function(x, t);
        if (product > 0)
        {
            a = x;
        }
        else
        {
            b = x;
            has_solution++;
        }
    }
    while(delta > epsilon);
    if (has_solution == 0) {
        x = 0;
    }
    return x;
}
double newton_method(double a, double b, double t, double epsilon, double x, double (*function)(double, double))
{
    double delta = 0;
    double derivative = 0;
    x = function(b, t);
    do
    {
        derivative = function(x+a, t) - function(x, t) / a;
        delta = function(x, t) / derivative;
        x -= delta;
    }
    while (fabs(delta)>epsilon);
    return x;
}
#endif
