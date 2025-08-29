#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "input_output.h"

void entry_message(void) {
    printf("\033[1;31mm\033[1;0m\033[1;32mi\033[1;0m\033[1;33ma\033[1;0m\033[1;34mu\033[1;0m\n\n");
}

void exit_message(void) {
    printf("\n\033[1;30mCOMMIT GITHUB, LEAVE BUILDING\033[1;0m\n");
}

void input_coeffs(equation_data *data)
{
    printf("\n\033[1;35mYour equation will look like this\033[1;0m: \033[1;36max^2+bx+c\033[1;0m\n\n");
    printf("\033[1;32mPlease enter coefficients\033[1;0m\n");

    data->coeff_a = check_input('a');
    data->coeff_b = check_input('b');
    data->coeff_c = check_input('c');
    return;
}

bool do_task(const char *do_task)
{
    char ch = 0;
    bool correct_input = 1;

    printf("%s", do_task);

    while (correct_input == 1)
    {
        if (scanf("%c", &ch)) {
            correct_input = 0;
        }
        if (clear_buffer()) {
            correct_input = 1;
        }
        if (correct_input == 1) {
            printf("\033[1;31mIncorrect input\033[1;0m\n"
                   "%s", do_task);
        }
    }
    if (ch == 'y')
        return 1;

    return 0;
}

void output_roots(equation_data *data)
{
    data->root_count = solver(data);

    switch (data->root_count)
    {
        case INF_ROOTS:
            printf("\033[1;37mInfinite amount of solutions\033[1;0m\n");
            break;
        case NO_ROOTS:
            printf("\033[1;31mNo solutions\033[1;0m\n");
            break;
        case ONE_ROOT:
            printf("\033[1;33mEquation has 1 solution, %lg\033[1;0m\n", data->root_1);
            break;
        case TWO_ROOTS:
            printf("\033[1;32mEquation has 2 solutions, %lg and %lg\033[1;0m\n", data->root_1, data->root_2);
            break;
        default:
            printf("How did you even get there?\n");
            break;
    }
}
