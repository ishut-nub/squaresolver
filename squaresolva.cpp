#include <stdio.h>
#include <math.h>

int main(void)
{
    double coef_a = 0, coef_b = 0, coef_c = 0;
    double root1 = 0, root2 = 0, dis = 0;

    printf("Enter equation coefficents: ");
    scanf("%lg %lg %lg", &coef_a, &coef_b, &coef_c);

    if (coef_a == 0 && coef_b == 0 && coef_c == 0)
        printf("Equation has infinite solutions\n");
    else if (coef_a == 0 && coef_b != 0 && coef_c != 0)
        printf("Equation has one solution, %lg\n", -coef_c / coef_b);
    else
    {
        dis = coef_b * coef_b - 4 * coef_a * coef_c;
        if (dis < 0)
            printf("Equation has no solutions\n");
        else if (dis==0)
            printf("Equation has 1 solution, %lg\n", (-coef_b/(2*coef_a)));
        else
        {
            root1 = (-coef_b + sqrt(dis)) / (2 * coef_a);
            root2 = (-coef_b - sqrt(dis)) / (2 * coef_a);
            printf("Equation has 2 solutions, %lg and %lg\n", root1, root2);
        }
    }
}

