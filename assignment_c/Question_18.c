#include<stdio.h>

int main()
{
    int num, pos, n, result;

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("Enter starting position: ");
    scanf("%d", &pos);

    printf("Enter number of bits: ");
    scanf("%d", &n);

    // shift bits to right
    num = num >> pos;

    // extract n bits
    result = num & ((1 << n) - 1);

    printf("Extracted bits value = %d", result);

    return 0;
}