#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
double validate_double_input(const char *prompt, double min)
{
    double value = 0 ;
    int input = 0;
    do
    {
        printf("%s", prompt);
        input = scanf("%lf", &value);
        if (input != 1 || value < min)
        {
            printf("Invalid input. Please enter a valid number.\n");
        }
        fflush(stdin);
    }
    while (input != 1 || value < min);
    return value;
}
#endif
