#include <stdio.h>
#include <conio.h>
#include "validation.h"
#include "calculation.h"
#define MINIMUM_VARIABLE -100
#define MAXIMUM_VARIABLE 100
#define MINIMUM_ACCURACY 1e-16
#define MAXIMUM_ACCURACY 1e-1

#define INTERVAL_STEP 0.01
#define MAX_ROOTS 100

int main()
{
    do
    {
        double t = 0, a = 0, b = 0, epsilon = 0;
        double (*chosen_function)(double, double) = 0;
        char user_choice = 0;

        printf("This program calculates nonlinear equations on given interval[a;b]\n");
        user_choice = validate_char_input("Press number of function you want to solve:\n"
        "1) cos(t/x) - 2 * sin(1/x) + 1/x\n"
        "2) sin(ln(x)) - cos(ln(x)) + t*ln(x)\n", '1', '2');
        switch (user_choice) {
            case '1':
                chosen_function = function1;
                printf("\n---YOUR CHOSEN FUNCTION---\ncos(t/x) - 2 * sin(1/x) + 1/x\n"
                                                                "Enter variables and accuracy\n");
                a = validate_double_input("\na = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, is_zero);
                b = validate_double_input("\nb = ", a, MAXIMUM_VARIABLE, is_zero);
                t = validate_double_input("\nt = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, any_number);
                epsilon = validate_double_input("\naccuracy = ", MINIMUM_ACCURACY, MAXIMUM_ACCURACY, any_number);
                break;
            case '2':
                chosen_function = function2;
                printf("\n---YOUR CHOSEN FUNCTION---\nsin(ln(x)) - cos(ln(x)) + t*ln(x)\n"
                                                                "Enter variables and accuracy");
                a = validate_double_input("\na = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, not_greater_than_one);
                b = validate_double_input("\nb = ", a, MAXIMUM_VARIABLE, not_greater_than_one);
                t = validate_double_input("\nt = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, any_number);
                epsilon = validate_double_input("\naccuracy = ", MINIMUM_ACCURACY, MAXIMUM_ACCURACY, any_number);
                break;
            default:
                printf("Error\n");
                break;
        }
        user_choice = validate_char_input("Press [1] (Half division method) or [2] (Newton method) to choose the method\n",
                    '1', '2');

        double step = INTERVAL_STEP;
        double start = a;
        int precision = fabs(log10(epsilon));
        int roots_found = 0;
        double roots[MAX_ROOTS] = {0};

        while (start < b) {
            double end = fmin(start + step, b);
            double f_start = chosen_function(start, t);
            double f_end = chosen_function(end, t);
            if (isnan(f_start) || isnan(f_end))
            {
                start = end;
                continue;
            }

            if (f_start * f_end <= 0)
            {
                double x = 0;
                switch (user_choice)
                {
                    case '1':
                        x = half_division_method(start, end, t, epsilon, chosen_function);
                        break;
                    case '2':
                        x = newton_method(start, end, t, epsilon, chosen_function);
                        break;
                    default:
                        printf("Error\n");
                        break;
                }
                if (is_unique_root(roots, roots_found, x, epsilon))
                {
                    roots[roots_found++] = x;
                    printf("Root #%02d: x = %.*lf\n", roots_found, precision, x);
                }
            }
            start = end;
        }
        if (roots_found == 0)
        {
            printf("No roots found in the given interval.\n");
        }
        printf("Press 'r' to restart the program, any other key to exit.\n");
    }
    while (getch() == 'r');
    return 0;
}

