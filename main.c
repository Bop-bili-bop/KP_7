#include <stdio.h>
#include <conio.h>
#include "validation.h"
#include "calculation.h"
#define MINIMUM_VARIABLE -50.0
#define MAXIMUM_VARIABLE 50.0
#define MINIMUM_T -100.0
#define MAXIMUM_T 100.0
#define MINIMUM_ACCURACY 1e-15
#define MAXIMUM_ACCURACY 1e-1
#define INTERVAL_STEP 1e-4
#define MAX_ROOTS 10000

int main()
{
    do
    {
        double t = 0, a = 0, b = 0, epsilon = 0;
        double (*chosen_equation)(double, double) = 0;
        char user_choice = 0;
        printf("This program calculates nonlinear equations on given interval[a;b]\n");
        user_choice = validate_char_input("Press number of equation you want to solve:\n"
        "1) cos(t/x) - 2 * sin(1/x) + 1/x = 0\n"
        "2) sin(ln(x)) - cos(ln(x)) + t*ln(x) = 0\n", '1', '2');
        switch (user_choice) {
            case '1':
                chosen_equation = equation_cos;
                printf("\n---YOUR CHOSEN EQUATION---\ncos(t/x) - 2 * sin(1/x) + 1/x = 0\n"
                                                                "Enter variables and accuracy\n");
                a = validate_double_input("\na [-50, 50] (a!=0) = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, is_zero);
                b = validate_double_input("\nb [a, 50] = ", a, MAXIMUM_VARIABLE, is_zero);
                t = validate_double_input("\nt [-100, 100] = ", MINIMUM_T, MAXIMUM_T, any_number);
                epsilon = validate_double_input("\naccuracy [1e-15, 1e-1] = ", MINIMUM_ACCURACY, MAXIMUM_ACCURACY, any_number);
                break;
            case '2':
                chosen_equation = equation_ln;
                printf("\n---YOUR CHOSEN EQUATION---\nsin(ln(x)) - cos(ln(x)) + t*ln(x) = 0\n"
                                                                "Enter variables and accuracy");
                a = validate_double_input("\na [1e-15,50] = ", 1e-15, MAXIMUM_VARIABLE, not_greater_than_zero);
                b = validate_double_input("\nb [a, 50] = ", a, MAXIMUM_VARIABLE, not_greater_than_zero);
                t = validate_double_input("\nt [-100, 100] = ", MINIMUM_T, MAXIMUM_T, any_number);
                epsilon = validate_double_input("\naccuracy [1e-15, 1e-1] = ", MINIMUM_ACCURACY, MAXIMUM_ACCURACY, any_number);
                break;
            default:
                printf("Error\n");
                break;
        }
        user_choice = validate_char_input("Press [1] (Half division method) or [2] (Newton method) to choose the method\n",
                    '1', '2');
        switch(user_choice) {
            case '1':
                printf("You chose Half division method\n");
                break;
            case '2':
                printf("You chose Newton method\n");
                break;
            default:
                printf("Error\n");
                break;
        }
        double step = INTERVAL_STEP;
        double start = a;
        int precision = fabs(log10(epsilon));
        int roots_found = 0;
        double roots[MAX_ROOTS] = {};

        while (start < b) {
            double end = fmin(start + step, b);
            double f_start = chosen_equation(start    , t);
            double f_end = chosen_equation(end, t);
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
                        x = half_division_method(start, end, t, epsilon, chosen_equation);
                        break;
                    case '2':
                        x = newton_method(start, end, t, epsilon, chosen_equation);
                        break;
                    default:
                        printf("Error\n");
                        break;
                }
                if (is_unique_root(roots, roots_found, x, epsilon) && !isnan(x) && fabs(x)>epsilon)
                {
                    roots[roots_found++] = x;
                    printf("Root #%03d: x = %.*lf\n", roots_found, precision, x);
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

