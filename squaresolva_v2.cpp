#include <stdio.h>
#include <math.h>
int main(void)
{
	double a=0,b=0,c=0;
	double x1=0,x2=0,d=0;
	scanf("%lg %lg %lg",&a,&b,&c);
	d=b*b-4*a*c;
	x1=(-b+sqrt(d))/(2*a);
	x2=(-b-sqrt(d))/(2*a);
	if (d<0)
		printf("Equation has no real roots\n");
	else if (d==0)
		printf("Equation has one solution, %lg\n", -b/(2*a));
	else
	{
	if (a==0 && b==0 && c==0)
                printf("Equation has infinite solutions\n");
        else if (a==0 && b!=0 && c!=0)
                printf("Equation is not quadratic, one solution - %lg\n", -c/b);
	else
		printf("Equation has 2 solutions, %lg and %lg\n", x1,x2);
	}
	return 0;
}

