#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "main.h"

int main(void)
{
    struct equation_data data = {.coeff_a = NAN, .coeff_b = NAN, .coeff_c = NAN,
                                 .root_1  = NAN, .root_2  = NAN, .root_count = NO_ROOTS};

    entry_message();

    if (do_task("Do tests? [y/n] ")) {
        run_test(&data);
    }

    input_coeffs(&data);

    solver(&data);

    output_roots(&data);

    while (do_task("Solve another equation? [y/n] "))
    {
        input_coeffs(&data);

        solver(&data);

        output_roots(&data);
    }

    exit_message();

    return 0;
}
