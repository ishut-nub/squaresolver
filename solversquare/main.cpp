#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "main.h"

int main(void)
{
    struct equation_data data = {.coeff_a = NAN, .coeff_b = NAN, .coeff_c = NAN,
                                 .root_1  = NAN, .root_2  = NAN, .root_count = NO_ROOTS};

    entry_message();

    if (do_task("\033[1;34mDo tests? [\033[1;0m\033[1;032my\033[1;0m\033[1;34m/\033[1;0m\033[1;31mn\033[1;0m\033[1;34m]\033[1;0m ")) {
        run_test(&data);
    }

    input_coeffs(&data);

    solver(&data);

    output_roots(&data);

    while (do_task("\033[1;34mSolve another equation? [\033[1;0m\033[1;032my\033[1;0m\033[1;34m/\033[1;0m\033[1;31mn\033[1;0m\033[1;34m]\033[1;0m "))
    {
        input_coeffs(&data);

        solver(&data);

        output_roots(&data);
    }

    exit_message();

    return 0;
}
