#include <stdio.h>
#include <TXLib.h>
#include <math.h>
int main()
{
    int a,b,c;      //���������� ���������� a b c
    double x1,x2,d; //���������� ���������� x1 x2 d � ��������� ������
    printf("���� ��������� ����� ��������� ���: ax^2+bx+c=0\n");
    printf("������� ����������� a, b � c ����� ������\n");
    scanf("%d %d %d", &a,&b,&c);   //������ �� a b c
    d=pow(pow(b,2)-4*a*c,0.5);     //������� �������������
    x1=(-b+d)/(2*a);               //������ ������
    x2=(-b-d)/(2*a);               //������ ������
    printf("����� ��������� ����� %f � %f\n",x1,x2);
    return 0;
}
