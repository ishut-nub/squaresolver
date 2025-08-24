#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

enum root_counter
{
    INF_ROOTS = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

const double ACCURACY_LIMIT = 0.00001;

void input_coeffs(double *coeff_a, double *coeff_b, double *coeff_c);

int linear_equation(double coeff_b, double coeff_c, double *root_1, double *root_2);
int quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2);
int solver(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2);

int compare_double(double test_x, double test_y);

double check_input(char symbol);

void clear_buffer(void);

int solver_tester(double test_coeff_a, double test_coeff_b, double test_coeff_c, double test_root_1, double test_root_2, root_counter test_root_count);
int run_test(void);

void output_roots(int root_count, double *root_1, double *root_2);

int main(void)
{
    double coeff_a = NAN, coeff_b = NAN, coeff_c = NAN;
    double root_1 = NAN, root_2 = NAN;
    int root_count = 0;

    input_coeffs(&coeff_a, &coeff_b, &coeff_c);

    assert(!(isnan(coeff_a)));
    assert(!(isnan(coeff_b)));
    assert(!(isnan(coeff_c)));

    root_count = solver(coeff_a, coeff_b, coeff_c, &root_1, &root_2);

    assert(!(isnan(root_1)));
    assert(!(isnan(root_2)));

    output_roots(root_count, &root_1, &root_2);

    int result = run_test();
    printf("Failed %d tests\n", result);
    return 0;
}

void input_coeffs(double *coeff_a, double *coeff_b, double *coeff_c)
{
    printf("Your equation will look like this: ax^2+bx+c\n");
    printf("Please enter coefficients\n");

    *coeff_a = check_input('a');
    *coeff_b = check_input('b');
    *coeff_c = check_input('c');
    return;
}

void output_roots(int root_count, double *root_1, double *root_2)
{
    switch (root_count)
    {
        case INF_ROOTS:
            printf("Infinite amount of solutions\n");
            break;
        case NO_ROOTS:
            printf("No solutions\n");
            break;
        case ONE_ROOT:
            printf("Equation has 1 solution, %lg\n", *root_1);
            break;
        case TWO_ROOTS:
            printf("Equation has 2 solutions, %lg and %lg\n", *root_1, *root_2);
            break;
        default:
            printf("How did you even get there?\n");
    }
}
int linear_equation(double coeff_b, double coeff_c, double *root_1, double *root_2)
{
    if (compare_double(coeff_b,0))
    {
        if (compare_double(coeff_c,0))
        {
            *root_1 = *root_2 = 0;
            return INF_ROOTS;
        }
        else
        {
            *root_1 = *root_2 = 0;
            return NO_ROOTS;
        }
    }
    else
    {
        *root_1 = *root_2 = (-coeff_c/coeff_b);
        return ONE_ROOT;
    }
}

int quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2)
{
    double discriminant = coeff_b * coeff_b - 4 * coeff_a * coeff_c;

    if (discriminant > 0)
    {
        *root_1 = (-coeff_b + sqrt(discriminant)) / (2 * coeff_a);
        *root_2 = (-coeff_b - sqrt(discriminant)) / (2 * coeff_a);
        return TWO_ROOTS;
    }
    else if (compare_double(discriminant, 0))
    {
        *root_1 = *root_2 = (-coeff_b / (2 * coeff_a));
        return ONE_ROOT;
    }
    else
    {
        *root_1 = *root_2 = 0;
        return NO_ROOTS;
    }
}

int solver(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2)
{
    if (compare_double(coeff_a, 0)) {
        return linear_equation(coeff_b, coeff_c, root_1, root_2);
    }
    return quadratic_equation(coeff_a, coeff_b, coeff_c, root_1, root_2);
}

int compare_double(double double_a, double double_b)
{
    return (fabs(double_a - double_b) < ACCURACY_LIMIT);
}

double check_input(char symbol)
{
    printf("Input %c\n", symbol);
    double number_input = 0;

    while (scanf("%lg", &number_input) != 1) {
        clear_buffer();
    }
    printf("%c = %lg\n", symbol, number_input);

    return number_input;
}
void clear_buffer(void)
{
    int ch = 0;

    while ((ch = getchar()) != '\n')
        putchar(ch);

    printf(" is not a number. \nPlease, re-enter your number \n");
}

int solver_tester(double test_coeff_a, double test_coeff_b, double test_coeff_c, double test_root_1, double test_root_2, root_counter test_root_count)
{
    double root_1 = NAN, root_2 = NAN;
    int root_count = solver(test_coeff_a, test_coeff_b, test_coeff_c, &root_1, &root_2);

    assert(!(isnan(root_1)));
    assert(!(isnan(root_2)));

    if (!(((compare_double(root_1, test_root_1) && compare_double(root_2, test_root_2)) || (compare_double(root_1, test_root_2) && compare_double(root_2, test_root_1))) && root_count == test_root_count))
    {
        printf("Test failed \nRoots %lg %lg instead of %lg %lg \nNumber of roots %d instead of %d\n", root_1, root_2, test_root_1, test_root_2, root_count, test_root_count);
        return 1;
    }
    else
        return 0;
}

int run_test()
{
    int test_failed = 0;
    test_failed += solver_tester(1, 3, -4,  1, -4, TWO_ROOTS);
    test_failed += solver_tester(0, 0,  0,  0,  0, INF_ROOTS);
    test_failed += solver_tester(0, 0,  1,  0,  0, NO_ROOTS);
    test_failed += solver_tester(0, 3, -3,  1,  1, ONE_ROOT);
    test_failed += solver_tester(1, 2,  1, -1, -1, ONE_ROOT);
    test_failed += solver_tester(1, 3,  5,  0,  0, NO_ROOTS);
    return test_failed;
}
