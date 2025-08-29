#include <stdio.h>
// Q 5. ) Find whether a number is even or odd

void checkNumber(int n)
{
    if (n == 0)
    {
        printf("the number is neither odd nor even");
    }

    else if (n & 1)
    {
        printf("the number %d is odd", n);
    }
    else
    {
        printf("the number %d is even", n);
    }
}
int main()
{

    int n;
    printf("enter the number");
    scanf("%d", &n);
    checkNumber(n);
    return 0;
}