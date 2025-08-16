#include <stdio.h>

float add(int a, int b)
{
    return (float)a + b;
}

void div(int a, int b)
{
    if (b != 0)
    {
        float result = (float)a / b;
        printf("The division of two numbers is: %f\n", result);
    }
    else
    {
        printf("Error: Division by zero is not allowed.\n");
    }
}

void mul(int a, int b)
{
    printf("Multiplication of two numbers is: %d\n", a * b);
}

int subtraction(int a, int b)
{

    printf("Subtraction of two numbers is: %d\n", a - b);
}

int main()
{

    int num1, num2, select;
    printf("Enter two integers ");
    scanf("%d %d", &num1, &num2);

    printf("enter number to choose an operation \n1)addition \n2)substration\n3)multiplication\n4)division");
    scanf("%d", &select);
    if (select == 1)
    {
        float sum = add(num2, num1);
        printf("The sum is: %f\n", sum);
    }
    else if (select == 2)
    {
        subtraction(num1, num2);
    }
    else if (select == 3)
    {
        mul(num1, num2);
    }

    else if (select == 4)
    {
        div(num1, num2);
    }
    else
    {
        printf("invalid number selected");
    }

    return 0;
}