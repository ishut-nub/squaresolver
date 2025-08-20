#include <stdio.h>
#include <TXLib.h>
#include <math.h>
int main()
{
    int a,b,c;      //объ€вление переменных a b c
    double x1,x2,d; //объ€вление переменных x1 x2 d с плавающей точкой
    printf("¬аше уравнение будет выгл€деть так: ax^2+bx+c=0\n");
    printf("¬ведите коэффиценты a, b и c через пробел\n");
    scanf("%d %d %d", &a,&b,&c);   //запрос на a b c
    d=pow(pow(b,2)-4*a*c,0.5);     //рассчет дискриминанта
    x1=(-b+d)/(2*a);               //первый корень
    x2=(-b-d)/(2*a);               //второй корень
    printf(" орни уравнени€ равны %f и %f\n",x1,x2);
    return 0;
}
