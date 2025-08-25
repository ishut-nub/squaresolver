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

int linear_equation(equation_info *info);
int quadratic_equation(equation_info *info);
int solver(equation_info *info);

int compare_double(double test_x, double test_y);
double find_min(double min_1, double min_2);
double find_max(double max_1, double max_2);

double check_input(char symbol);

void clear_buffer(void);

int solver_tester(test_data *test, equation_info *info);
int run_test(equation_info *info);

void output_roots(equation_info *info);

int main(void)
{
    struct equation_info info = {.coeff_a = NAN, .coeff_b = NAN, .coeff_c = NAN, .root_1 = NAN, .root_2 = NAN, .root_count = NO_ROOTS};
    input_coeffs(&info);

//    assert(!(isnan(info.coeff_a)));
//    assert(!(isnan(info.coeff_b)));
//    assert(!(isnan(info.coeff_c)));

    info.root_count = solver(&info);

    output_roots(&info);

    int result = run_test(&info);
    printf("Failed %d tests\n", result);
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
    double number_input = 0;

    while (scanf("%lg", &number_input) != 1) {

        clear_buffer();
    }
    printf("%c = %lg\n", symbol, number_input);

    return number_input;
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
        info->root_1 = find_min((-info->coeff_b + sqrt_discriminant) / (2 * info->coeff_a), (-info->coeff_b - sqrt_discriminant) / (2 * info->coeff_a));
        info->root_2 = find_max((-info->coeff_b + sqrt_discriminant) / (2 * info->coeff_a), (-info->coeff_b - sqrt_discriminant) / (2 * info->coeff_a));
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

void clear_buffer(void)
{
    int ch = 0;

    while ((ch = getchar()) != '\n')
        putchar(ch);

    printf(" is not a number. \nPlease, re-enter your number \n");
}

int solver_tester(test_data *test, equation_info *info)
{
    info->root_count = solver(info);

    if (!(compare_double(find_min(info->root_1, info->root_2), find_min(test->compare_root_1, test->compare_root_2)) && compare_double(find_max(info->root_1, info->root_2),find_max(test->compare_root_1, test->compare_root_2)) && info->root_count == test->compare_root_count))
    {
        printf("Test failed \nRoots %lg %lg instead of %lg %lg \n", info->root_1, info->root_2, test->compare_root_1, test->compare_root_2);
        printf("Number of roots %d instead of %d\n", info->root_count, test->compare_root_count);
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
        {.compare_coeff_a =  1, .compare_coeff_b =  3, .compare_coeff_c = -4, .compare_root_1 =  -4, .compare_root_2 =   1, .compare_root_count = TWO_ROOTS},
        {.compare_coeff_a =  0, .compare_coeff_b =  0, .compare_coeff_c =  0, .compare_root_1 = NAN, .compare_root_2 = NAN, .compare_root_count = INF_ROOTS},
        {.compare_coeff_a =  0, .compare_coeff_b =  0, .compare_coeff_c =  1, .compare_root_1 = NAN, .compare_root_2 = NAN, .compare_root_count =  NO_ROOTS},
        {.compare_coeff_a =  0, .compare_coeff_b =  3, .compare_coeff_c = -3, .compare_root_1 =   1, .compare_root_2 =   1, .compare_root_count =  ONE_ROOT},
        {.compare_coeff_a =  1, .compare_coeff_b =  2, .compare_coeff_c =  1, .compare_root_1 =  -1, .compare_root_2 =  -1, .compare_root_count =  ONE_ROOT},
        {.compare_coeff_a =  1, .compare_coeff_b =  3, .compare_coeff_c =  5, .compare_root_1 = NAN, .compare_root_2 = NAN, .compare_root_count =  NO_ROOTS},
        {.compare_coeff_a = -1, .compare_coeff_b = -3, .compare_coeff_c =  4, .compare_root_1 =  -4, .compare_root_2 =   1, .compare_root_count = TWO_ROOTS},
    };
    size_t size = sizeof(tests)/sizeof(tests[0]);
    for (long unsigned int i = 0; i<size; i++) {
        test_failed += solver_tester(&tests[i], info);

    }
    return test_failed;
}

double find_min(double min_1, double min_2)
{
    if (!(isnan(min_1)) && (isnan(min_2)))
        return min_1;
    if (isnan(min_1) && (!(isnan(min_2))))
        return min_2;
    if (isnan(min_1) && isnan(min_2))
        return min_1;
    return (min_1 <= min_2)? min_1 : min_2;
}

double find_max(double max_1, double max_2)
{
    if (!(isnan(max_1)) && (isnan(max_2)))
        return max_1;
    if (isnan(max_1) && (!(isnan(max_2))))
        return max_2;
    if (isnan(max_1) && isnan(max_2))
        return max_1;
    return (max_1 >= max_2)? max_1 : max_2;
}
