#include<stdio.h>

int main()
{
    int n1, n2, pos, n;
    int mask, a, b;

    printf("Enter first number: ");
    scanf("%d", &n1);

    printf("Enter second number: ");
    scanf("%d", &n2);

    printf("Enter starting position: ");
    scanf("%d", &pos);

    printf("Enter number of bits to swap: ");
    scanf("%d", &n);

    // create mask
    mask = (1 << n) - 1;

    // get bits from numbers
    a = (n1 >> pos) & mask;
    b = (n2 >> pos) & mask;

    // clear bits in original numbers
    n1 = n1 & ~(mask << pos);
    n2 = n2 & ~(mask << pos);

    // put swapped bits
    n1 = n1 | (b << pos);
    n2 = n2 | (a << pos);

    printf("After swapping bits:\n");
    printf("First number = %d\n", n1);
    printf("Second number = %d\n", n2);

    return 0;
}