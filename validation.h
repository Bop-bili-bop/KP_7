#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <conio.h>
char is_zero(double value)
{
    return value == 0;
}
char not_greater_than_zero(double value) {
    return value <= 0;
}
char any_number(double value) {
    return 0;
}
double validate_double_input(const char *prompt, double min, double max, char (*condition)(double))
{
    double value = 0;
    int input = 0;
    do
    {
        printf("%s", prompt);
        input = scanf("%lf", &value);
        if (input != 1 || value < min || value > max || condition(value))
        {
            printf("Invalid input. Please enter a valid number.\n");
        }
        fflush(stdin);
    }
    while (input != 1 || value < min || value > max || condition(value));
    return value;
}
char validate_char_input(char *prompt, char choice_1, char choice_2)
{
    char user_choice = 0;
    do
    {
        printf("%s", prompt);
        user_choice = getch();
        if (user_choice != choice_1 && user_choice != choice_2)
        {
            printf("Invalid input.\n");
        }
        fflush(stdin);
    }
    while (user_choice != choice_1 && user_choice != choice_2);
    return user_choice;
}
#endif
