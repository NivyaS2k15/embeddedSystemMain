#include<stdio.h>

int main()
{
    int a, b, pos, n;
    int mask, temp, result;

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    printf("Enter starting position: ");
    scanf("%d", &pos);

    printf("Enter value of n: ");
    scanf("%d", &n);

    // create mask
    mask = (1 << n) - 1;

    // take n bits from second number
    temp = b & mask;

    // clear bits in first number
    a = a & ~(mask << pos);

    // replace bits
    result = a | (temp << pos);

    printf("Result after replacing bits = %d", result);

    return 0;
}