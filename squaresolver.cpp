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

const double ACCURACY_LIMIT = 1e-15;

struct test_data
{
    double compare_coeff_a, compare_coeff_b, compare_coeff_c;
    double compare_root_1, compare_root_2;
    int compare_root_count;
};

struct equation_info
{
    double coeff_a, coeff_b, coeff_c;
    double root_1, root_2;
    int root_count;
};

void input_coeffs(equation_info *info);
void output_roots(equation_info *info);
int another_equation(void);

int linear_equation(equation_info *info);
int quadratic_equation(equation_info *info);
int solver(equation_info *info);

int compare_double(double test_x, double test_y);
double find_min(double min_1, double min_2);
double find_max(double max_1, double max_2);

double check_input(char symbol);

int clear_buffer(void);

int solver_tester(test_data *test, equation_info *info);
int run_test(equation_info *info);
int compare_test_roots(test_data *test, equation_info *info);

int main(void)
{
    printf("miau\n\n");
    struct equation_info info = {.coeff_a = NAN, .coeff_b = NAN, .coeff_c = NAN,
                                 .root_1 = NAN, .root_2 = NAN, .root_count = NO_ROOTS};

    int result = run_test(&info);
    printf("Failed %d tests\n\n", result);

    restart:

    input_coeffs(&info);

    info.root_count = solver(&info);

    output_roots(&info);

    if (another_equation())
        goto restart;
    printf("COMMIT GITHUB, LEAVE BUILDING\n");
    return 0;
}

void input_coeffs(equation_info *info)
{
    printf("Your equation will look like this: ax^2+bx+c\n");
    printf("Please enter coefficients\n");

    info->coeff_a = check_input('a');
    info->coeff_b = check_input('b');
    info->coeff_c = check_input('c');
    return;
}

double check_input(char symbol)
{
    printf("Input %c\n", symbol);
    int ch = 1;
    double number_input = NAN;
    while (ch == 1)
    {
        if (scanf("%lg", &number_input))
            ch = 0;
        if (clear_buffer())
            ch = 1;
        if (ch == 1)
            printf("Incorrect input\n"
                   "Input %c\n", symbol);
    }
    return number_input;
}

int clear_buffer(void)
{
    int ch = 0;

    while (getchar() != '\n')
        ch++;
    return ch;
}

void output_roots(equation_info *info)
{
    switch (info->root_count)
    {
        case INF_ROOTS:
            printf("Infinite amount of solutions\n");
            break;
        case NO_ROOTS:
            printf("No solutions\n");
            break;
        case ONE_ROOT:
            printf("Equation has 1 solution, %lg\n", info->root_1);
            break;
        case TWO_ROOTS:
            printf("Equation has 2 solutions, %lg and %lg\n", info->root_1, info->root_2);
            break;
        default:
            printf("How did you even get there?\n");
    }
}
int linear_equation(equation_info *info)
{
    if (compare_double(info->coeff_b,0))
    {
        if (compare_double(info->coeff_c,0))
        {
            return INF_ROOTS;
        }
        else
        {
            return NO_ROOTS;
        }
    }
    else
    {
        info->root_1 = info->root_2 = (-info->coeff_c/info->coeff_b);
        return ONE_ROOT;
    }
}

int quadratic_equation(equation_info *info)
{
    double discriminant = info->coeff_b * info->coeff_b - 4 * info->coeff_a * info->coeff_c;
    double sqrt_discriminant = sqrt(discriminant);

    if (discriminant > 0)
    {
        info->root_1 = find_min((-info->coeff_b + sqrt_discriminant) / (2 * info->coeff_a),
                                (-info->coeff_b - sqrt_discriminant) / (2 * info->coeff_a));
        info->root_2 = find_max((-info->coeff_b + sqrt_discriminant) / (2 * info->coeff_a),
                                (-info->coeff_b - sqrt_discriminant) / (2 * info->coeff_a));
        return TWO_ROOTS;
    }
    else if (compare_double(discriminant, 0))
    {
        info->root_1 = info->root_2 = (-info->coeff_b / (2 * info->coeff_a));
        return ONE_ROOT;
    }
    else
    {
        return NO_ROOTS;
    }
}

int solver(equation_info *info)
{
    assert(!(isnan(info->coeff_a)));
    assert(!(isnan(info->coeff_b)));
    assert(!(isnan(info->coeff_c)));

    if (compare_double(info->coeff_a, 0)) {
        return linear_equation(info);
    }
    return quadratic_equation(info);
}

int compare_double(double double_a, double double_b)
{
    if (!(isnan(double_a)) && (isnan(double_b)))
        return 1;
    if (isnan(double_a) && (!(isnan(double_b))))
        return 1;
    if (isnan(double_a) && isnan(double_b))
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

int solver_tester(test_data *test, equation_info *info)
{
    info->coeff_a = test->compare_coeff_a;
    info->coeff_b = test->compare_coeff_b;
    info->coeff_c = test->compare_coeff_c;

    assert(!(isnan(info->coeff_a)));
    assert(!(isnan(info->coeff_b)));
    assert(!(isnan(info->coeff_c)));

    info->root_count = solver(info);

    if (!(compare_test_roots(test, info) && (info->root_count == test->compare_root_count)))
    {
        printf("Test failed \nRoots %lg %lg instead of %lg %lg \n"
               "Number of roots %d instead of %d\n\n",
               info->root_1, info->root_2, test->compare_root_1, test->compare_root_2,
               info->root_count, test->compare_root_count);
        return 1;
    }
    else
        return 0;
}

int run_test(equation_info *info)
{
    int test_failed = 0;
    test_data tests[] =
    {
        { 1,  3, -4,  -4,   1, TWO_ROOTS},
        { 0,  0,  0, NAN, NAN, INF_ROOTS},
        { 0,  0,  1, NAN, NAN,  NO_ROOTS},
        { 0,  3, -3,   1,   1,  ONE_ROOT},
        { 1,  2,  1,  -1,  -1,  ONE_ROOT},
        { 1,  3,  5, NAN, NAN,  NO_ROOTS},
        {-1, -3,  4,  -4,   1, TWO_ROOTS},
    };

    size_t size = sizeof(tests)/sizeof(tests[0]);

    for (long unsigned int i = 0; i < size; i++) {
        test_failed += solver_tester(&tests[i], info);
    }
    return test_failed;
}

int compare_test_roots(test_data *test, equation_info *info)
{
    double min_root = NAN;
    double max_root = NAN;
    double min_compare_root = NAN;
    double max_compare_root = NAN;

    min_root = find_min(info->root_1, info->root_2);
    max_root = find_max(info->root_1, info->root_2);
    min_compare_root = find_min(test->compare_root_1, test->compare_root_2);
    max_compare_root = find_max(test->compare_root_1, test->compare_root_2);

    if (compare_double(min_root, min_compare_root) && compare_double(max_root, max_compare_root))
        return 1;
    return 0;
}

int another_equation(void)
{
    char ch = 0;

    printf("Solve another equation? [y/n] ");
    scanf("%c", &ch);

    if (ch == 'y')
        return 1;
    return 0;
}
