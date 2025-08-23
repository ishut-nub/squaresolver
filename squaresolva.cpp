#include <stdio.h>
#include <math.h>

void input(void);
int count_solves(double a, double b, double c, double * root_1, double * root_2);
void output(int root_count, double * root_1, double * root_2);

int main(void)
{
    double coeff_a = 0, coeff_b = 0, coeff_c = 0;
    double root_1 = 0, root_2 = 0;
    int root_count = 0;
    input();
    scanf("%lg %lg %lg", &coeff_a, &coeff_b, &coeff_c); //warning: ignoring return value of ‘int scanf(const char*, ...)’ declared with attribute ‘warn_unused_result’ [-Wunused-result]
    // printf("%lg %lg %lg\n", coeff_a, coeff_b, coeff_c); //checking
    root_count = count_solves(coeff_a, coeff_b, coeff_c, &root_1, &root_2);
    output(root_count, &root_1, &root_2);
}

void input(void)
{
    printf("Your equation will look like this: ax^2+bx+c\n");
    printf("Please enter a, b and c coefficents: ");
}

int count_solves(double a, double b, double c, double * root_1, double * root_2)
{
    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
                return -1;
            else
                return 0;
        }
        else
        {
            *root_1 = (-c/b);
            return 1;
        }
    }
    else
    {
        int discriminant = 0;
        discriminant = b * b - 4 * a * c;
        if (discriminant > 0)
        {
            *root_1 = (-b + sqrt(discriminant))/(2*a);
            *root_2 = (-b - sqrt(discriminant))/(2*a);
            return 2;
        }
        else if (discriminant == 0)
        {
            *root_1 = *root_2 = (-b/(2*a));
            return 1;
        }
        else
            return 0;
    }
}

void output(int root_count, double * root_1, double * root_2)
{
    switch (root_count)
    {
        case -1: printf("Infinite amount of solutions\n");
                 break;
        case 0:  printf("No solutions\n");
                 break;
        case 1:  printf("Equation has 1 solution - %lg\n", *root_1);
                 break;
        case 2:  printf("Equation has 2 solutions - %lg and %lg\n", *root_1, *root_2);
                 break;
        default: printf("How did you even get there?");
    }
}
