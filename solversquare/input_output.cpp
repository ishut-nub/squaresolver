#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "input_output.h"

void entry_message(void) {
    printf("miau\n\n");
}

void exit_message(void) {
    printf("\nCOMMIT GITHUB, LEAVE BUILDING\n");
}

void input_coeffs(equation_data *data)
{
    printf("\nYour equation will look like this: ax^2+bx+c\n\n");
    printf("Please enter coefficients\n");

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
            printf("Incorrect input\n"
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
            printf("Infinite amount of solutions\n");
            break;
        case NO_ROOTS:
            printf("No solutions\n");
            break;
        case ONE_ROOT:
            printf("Equation has 1 solution, %lg\n", data->root_1);
            break;
        case TWO_ROOTS:
            printf("Equation has 2 solutions, %lg and %lg\n", data->root_1, data->root_2);
            break;
        default:
            printf("How did you even get there?\n");
            break;
    }
}
