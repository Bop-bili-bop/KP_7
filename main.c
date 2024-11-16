#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "validation.h"
#include "calculation.h"
int main()
{
    do {
        double t = 0, a = 0, b = 0, epsilon = 0, delta = 0, x = 0, dobutok = 0;
        double (*FunctionArray[2]) = {func1, func2};
        a = validate_double_input("a = ", 1e-15);
        b = validate_double_input("\nb = ", a);
        t = validate_double_input("\nt = ", 1e-15);
        epsilon = validate_double_input("\naccuracy = ", 1e-15);
        do
        {
            x = (a + b) / 2.0;
            delta = fabs(b - a);
            dobutok = (*func1)(x, a) * (*func1)(x, b);
            if (dobutok > 0)
            {
                a = x;
            }
            else
            {
                b = x;
            }
        }
        while(delta > epsilon);
        printf("\nx = %f\n", x);
        printf("Press 'r' to restart the program, any other key to exit.\n");
    }
    while (getch() == 'r');
    return 0;
}
