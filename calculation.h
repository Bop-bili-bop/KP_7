#ifndef CALCULATION_H
#define CALCULATION_H
#include <math.h>

#define STEP 1e-6
#define MAX_ITER 1e6
#define MIN_DERIVATIVE 1e-12

double function1 (double x, double t)
{
    return cos(t/x) - 2.0 * sin(1/x) + 1.0/x;
}
double function2 (double x, double t)
{
    return sin(log(x)) - cos(log(x)) + t*log(x);
}
double half_division_method(double a, double b, double t, double epsilon, double (*function)(double, double)) {
    double delta = 0;
    int iterations = 0;
    double x = 0, fa = 0, fx = 0;
    do {
        x = (a + b) / 2.0;
        delta = fabs(b - a);

        fa = function(a, t);
        fx = function(x, t);

        if (isnan(fa) || isnan(fx))
        {
            printf("Function has a discontinuity in the interval [%lf, %lf]. Skipping...\n", a, b);
            return NAN;
        }

        if (fa * fx > 0)
        {
            a = x;
        }
        else
        {
            b = x;
        }

        iterations++;
        if (iterations > MAX_ITER)
        {
            printf("Maximum iterations reached. The method may not converge.\n");
            return NAN;
        }
    } while (delta > epsilon);

    return x;
}

double newton_method(double a, double b, double t, double epsilon, double (*function)(double, double)) {
    double delta = 0;
    double derivative = 0;
    int iterations = 0;

    double x = (a + b) / 2.0;

    do {
        double fx = function(x, t);
        if (isnan(fx))
        {
            printf("Function is undefined at x = %lf. Skipping...\n", x);
            return NAN;
        }
        derivative = (function(x + STEP, t) - fx) / STEP;

        if (fabs(derivative) < MIN_DERIVATIVE) {
            printf("Derivative too small at x = %lf. The method may not converge.\n", x);
            return NAN;
        }
        delta = fx / derivative;
        x -= delta;

        iterations++;
        if (iterations > MAX_ITER) {
            printf("Maximum iterations reached. The method may not converge.\n");
            return NAN;
        }
    } while (fabs(delta) > epsilon);

    return x;
}

#endif
