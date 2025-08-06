#include <stdio.h>

float add(float a, float b)
{
    float sum = a + b;
    return sum;
}

void div(int a, int b)
{

    float div = a / b;
    printf("the division of two numbers is  :%f\n", div);
}

void mul(int a, int b);

int subbtration(int a, int b)
{
    int sub = a - b;
    return sub;
}

int main()
{

    float sum = add(2.5, 3.6);
    printf("the sum is %f\n", sum);

    div(9, 3);
    mul(3, 5);
    int sub = subbtration(5, 2);
    printf("substraction of two number is %d", sub);

    return 0;
}

void mul(int a, int b)
{
    printf("multiplication of two number are %d\n", (a * b));
}