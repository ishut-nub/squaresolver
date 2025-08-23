#include <stdio.h>
#include <math.h>
#define INF_ROOTS -1
#define NO_ROOTS 0
#define ONE_ROOT 1
#define TWO_ROOTS 2

void input(double *coeff_a, double *coeff_b, double *coeff_c);
int linear_equation(double coeff_b, double coeff_c, double *root_1);
int quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2);
int solver(double coeff_a, double coeff_b, double coeff_c, double *root_1, double *root_2);
void output(int root_count, double *root_1, double *root_2);

int main(void)
{
    double coeff_a = 0, coeff_b = 0, coeff_c = 0;
    double root_1 = 0, root_2 = 0;
    int root_count = 0;
    input(&coeff_a, &coeff_b, &coeff_c);
    root_count = solver(coeff_a, coeff_b, coeff_c, &root_1, &root_2);
    output(root_count, &root_1, &root_2);
}

void input(double *coeff_a, double *coeff_b, double *coeff_c)
{
    printf("Your equation will look like this: ax^2+bx+c\n");
    printf("Please enter a, b and c coefficents: ");
    while (scanf("%lg %lg %lg", coeff_a, coeff_b, coeff_c)!=3)
    {
        printf("Incorrect input. Try again\n");
        scanf("%lg %lg %lg", coeff_a, coeff_b, coeff_c);
    }
}

void output(int root_count, double *root_1, double *root_2)
{
    switch (root_count)
    {
        case INF_ROOTS: printf("Infinite amount of solutions\n");
                 break;
        case NO_ROOTS:  printf("No solutions\n");
                 break;
        case ONE_ROOT:  printf("Equation has 1 solution, %lg\n", *root_1);
                 break;
        case TWO_ROOTS:  printf("Equation has 2 solutions, %lg and %lg\n", *root_1, *root_2);
                 break;
        default: printf("How did you even get there?\n");
    }
}
int linear_equation(double coeff_b, double coeff_c, double *root_1)
{
    if (coeff_b == 0)
    {
        if (coeff_c == 0) {
            return INF_ROOTS;
        }
        else {
            return NO_ROOTS;
        }
    }
    else
    {
        *root_1 = (-coeff_c/coeff_b);
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
    else if (discriminant == 0)
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
    if (coeff_a == 0) {
        return linear_equation(coeff_b, coeff_c, root_1);
        }
    else {
        return quadratic_equation(coeff_a, coeff_b, coeff_c, root_1, root_2);
    }
}
