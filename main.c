#include <stdio.h>
#include <conio.h>
#include "validation.h"
#include "calculation.h"
#define MINIMUM_VARIABLE -1e3
#define MAXIMUM_VARIABLE 1e3
#define MINIMUM_ACCURACY 1e-15
#define MAXIMUM_ACCURACY 1e-1
int main()
{
    do
    {
        double t = 0, a = 0, b = 0, epsilon = 0, x = 0;
        double (*chosen_function)(double, double) = 0;
        char choice = 0, user_function_choice = 0;
        printf("This program calculates nonlinear equations on given interval[a;b]\n");
        user_function_choice = validate_char_input("Press number of function you want to solve:\n"
        "1) cos(t/x) - 2 * sin(1/x) + 1/x\n"
        "2) sin(log(x)) - cos(log(x)) + t*log(x)\n", '1', '2');
        switch (user_function_choice) {
            case '1':
                chosen_function = function1;
                printf("\n---YOUR CHOSEN FUNCTION---\ncos(t/x) - 2 * sin(1/x) + 1/x\n"
                                                                "Enter variables and accuracy\n");
                a = validate_double_input("\na = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, is_zero);
                b = validate_double_input("\nb = ", a, MAXIMUM_VARIABLE, is_zero);
                t = validate_double_input("\nt = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, is_zero);
                epsilon = validate_double_input("\naccuracy = ", MINIMUM_ACCURACY, MAXIMUM_ACCURACY, is_zero);
                break;
            case '2':
                chosen_function = function2;
                printf("\n---YOUR CHOSEN FUNCTION---\nsin(log(x)) - cos(log(x)) + t*log(x)\n"
                                                                "Enter variables and accuracy");
                a = validate_double_input("\na = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, is_zero);
                b = validate_double_input("\nb = ", a, MAXIMUM_VARIABLE, is_zero);
                t = validate_double_input("\nt = ", MINIMUM_VARIABLE, MAXIMUM_VARIABLE, is_zero);
                epsilon = validate_double_input("\naccuracy = ", MINIMUM_ACCURACY, MAXIMUM_ACCURACY, is_zero);
                break;
            default:
                printf("Error\n");
                break;
        }
        choice = validate_char_input("Press [1] (Half division method) or [2] (Newton method) to choose the method\n",
            '1', '2');
        switch (choice)
        {
            case '1':
                x = half_division_method(a, b, t, epsilon, x, chosen_function);
                break;
            case '2':
                x = newton_method(a, b, t, epsilon, x, chosen_function);
                break;
            default:
                printf("Error\n");
                break;
        }
        int precision = fabs(log10(epsilon));
        if (x < a || x > b || x == 0)
        {
            printf("No x in given interval\n");
        }
        else
        {
            printf("x = %.*lf\n", precision, x);
        }
        printf("Press 'r' to restart the program, any other key to exit.\n");
    }
    while (getch() == 'r');
    return 0;
}
