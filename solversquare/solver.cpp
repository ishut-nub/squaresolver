#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "solver.h"

root_counter linear_equation(equation_data *data)
{
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));

    if (doubles_equality(data->coeff_b, 0))
    {
        if (doubles_equality(data->coeff_c, 0)) {
            return INF_ROOTS;
        }
        else {
            return NO_ROOTS;
        }
    }
    data->root_1 = data->root_2 = (-data->coeff_c / data->coeff_b);
    return ONE_ROOT;
}

root_counter quadratic_equation(equation_data *data)
{
    assert(!(isnan(data->coeff_a)));
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));

    double discriminant = data->coeff_b * data->coeff_b - 4 * data->coeff_a * data->coeff_c;
    double sqrt_discriminant = sqrt(discriminant);

    if (discriminant < 0) {
        return NO_ROOTS;
    }
    else if (doubles_equality(discriminant, 0)) {
        data->root_1 = data->root_2 = (-data->coeff_b / (2 * data->coeff_a));
        return ONE_ROOT;
    }
    data->root_1 = find_min((-data->coeff_b + sqrt_discriminant) / (2 * data->coeff_a),
                            (-data->coeff_b - sqrt_discriminant) / (2 * data->coeff_a));
    data->root_2 = find_max((-data->coeff_b + sqrt_discriminant) / (2 * data->coeff_a),
                            (-data->coeff_b - sqrt_discriminant) / (2 * data->coeff_a));
    return TWO_ROOTS;
}

root_counter solver(equation_data *data)
{
    assert(!(isnan(data->coeff_a)));
    assert(!(isnan(data->coeff_b)));
    assert(!(isnan(data->coeff_c)));
    assert(data);

    if (doubles_equality(data->coeff_a, 0)) {
        return linear_equation(data);
    }
    return quadratic_equation(data);
}
