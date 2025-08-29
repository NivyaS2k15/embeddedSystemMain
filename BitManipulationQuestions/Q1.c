#include <stdio.h>
// Q 1. )Check if the ith bit is set or not

void printBin(int n)
{

    for (int i = 31; i >= 0; i--)
    {

        if (n & (1 << i))
            printf("1");
        else
            printf("0");
    }
}
void SetBit(int n, int pos)
{
    int mask = 1 << (pos - 1);
    n = n | mask;

    printf("the value of the position %d is \n:", pos);

    printBin(n);
}

int main()
{
    int num, pos;
    printf("enter the number");
    scanf("%d", &num);

    printf("enter the position");
    scanf("%d", &pos);
    SetBit(num, pos);

    return 0;
}