#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "utility.h"

double check_input(char symbol)
{
    bool correct_input = 1;
    double number_input = NAN;

    printf("\033[1;36mInput %c\033[1;0m\n", symbol);

    while (correct_input == 1)
    {
        if (scanf("%lg", &number_input)) {
            correct_input = 0;
        }
        if (clear_buffer()) {
            correct_input = 1;
        }
        if (correct_input == 1) {
            printf("\033[1;31mIncorrect input\033[1;0m\n"
                   "\033[1;36mInput %c\033[1;0m\n", symbol);
        }
    }
    return number_input;
}

int clear_buffer(void)
{
    int buffer_clear = 0;

    while (getchar() != '\n')
        buffer_clear++;
    return buffer_clear;
}

int doubles_equality(double double_a, double double_b)
{
    bool isnan_a = (isnan(double_a));
    bool isnan_b = (isnan(double_b));

    if ((!(isnan_a)) && isnan_b)
        return 1;
    if (isnan_a && (!(isnan_b)))
        return 1;
    if (isnan_a && isnan_b)
        return 1;
    return (fabs(double_a - double_b) < ACCURACY_LIMIT);
}

double find_min(double min_1, double min_2)
{
    if (!(isnan(min_1)) && (isnan(min_2)))
        return min_1;
    if (isnan(min_1) && (!(isnan(min_2))))
        return min_2;
    if (isnan(min_1) && isnan(min_2))
        return min_1;
    return fmin(min_1, min_2);
}

double find_max(double max_1, double max_2)
{
    if (!(isnan(max_1)) && (isnan(max_2)))
        return max_1;
    if (isnan(max_1) && (!(isnan(max_2))))
        return max_2;
    if (isnan(max_1) && isnan(max_2))
        return max_1;
    return fmax(max_1, max_2);
}
