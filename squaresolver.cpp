#include <stdio.h>
#include <math.h>
#include <ctype.h>

enum root_count {NO_ROOTS, ONE_ROOT, TWO_ROOTS, INF_ROOTS};

const double ACCURACY_LIMIT = 0.00001;

void input_coeffs(double *coeff_a, double *coeff_b, double *coeff_c);
int linear_equation(double coeff_b, double coeff_c, double *root_1, double *root_2);
int quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2);
int solver(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2);
int check_accuracy(double test_x, double test_y);
double number_check(void);
int test_solve(double test_coeff_a, double test_coeff_b, double test_coeff_c, double test_root_1, double test_root_2, int test_root_count);
int run_test(void);
void output_roots(int root_count, double *root_1, double *root_2);

int main(void)
{
    double coeff_a = 0, coeff_b = 0, coeff_c = 0;
    double root_1 = 0, root_2 = 0;
    int root_count = 0;
    input_coeffs(&coeff_a, &coeff_b, &coeff_c);
    root_count = solver(coeff_a, coeff_b, coeff_c, &root_1, &root_2);
    output_roots(root_count, &root_1, &root_2);
    int result = run_test();
    printf("Failed %d tests\n", result);
    return 0;
}

void input_coeffs(double *coeff_a, double *coeff_b, double *coeff_c)
{
    printf("Your equation will look like this: ax^2+bx+c\n");
    printf("Please enter a, b and c coefficents: ");

    *coeff_a = number_check();
    *coeff_b = number_check();
    *coeff_c = number_check();

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
    if (check_accuracy(coeff_b,0))
    {
        if (check_accuracy(coeff_c,0)) {
            return INF_ROOTS;
        }
        else {
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
        *root_1 = (-coeff_b + sqrt(discriminant))/(2*coeff_a);
        *root_2 = (-coeff_b - sqrt(discriminant))/(2*coeff_a);
        return TWO_ROOTS;
    }
    else if (check_accuracy(discriminant,0))
    {
        *root_1 = *root_2 = (-coeff_b/(2*coeff_a));
        return ONE_ROOT;
    }
    else {
        return NO_ROOTS;
    }
}

int solver(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2)
{
    if (check_accuracy(coeff_a,0)) {
        return linear_equation(coeff_b, coeff_c, root_1, root_2);
    }
    else {
        return quadratic_equation(coeff_a, coeff_b, coeff_c, root_1, root_2);
    }
}

int check_accuracy(double test_x, double test_y)
{
    if (fabs(test_x-test_y)<ACCURACY_LIMIT)
        return 1;
    else
        return 0;
}

double number_check(void)
{
    double number_input = 0;
    char false_ch;
    while (scanf("%lg", &number_input) != 1)
    {
        while ((false_ch = getchar()) != '\n')
        {
            putchar(false_ch);
            printf(" is not a number. \nPlease, re-enter your number \n");
        }
    }
    return number_input;
}
int test_solve(double test_coeff_a, double test_coeff_b, double test_coeff_c, double test_root_1, double test_root_2, int test_root_count)
{
    double root_1 = 0, root_2 = 0;
    int root_count = solver(test_coeff_a, test_coeff_b, test_coeff_c, &root_1, &root_2);
    if (!(((check_accuracy(root_1, test_root_1) && check_accuracy(root_2, test_root_2)) || (check_accuracy(root_1, test_root_2) && check_accuracy(root_2, test_root_1))) && check_accuracy(root_count, test_root_count)))
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
    test_failed += test_solve(1, 3, -4,  1, -4, 2);
    test_failed += test_solve(0, 0,  0,  0,  0, 3);
    test_failed += test_solve(0, 0,  1,  0,  0, 0);
    test_failed += test_solve(0, 3, -3,  1,  1, 1);
    test_failed += test_solve(1, 2,  1, -1, -1, 1);
    test_failed += test_solve(1, 3,  5,  0,  0, 0);
    return test_failed;
}
