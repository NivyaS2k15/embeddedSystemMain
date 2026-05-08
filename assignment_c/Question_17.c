#include<stdio.h>

int main()
{
    int num, pos, n, mask, result;

    printf("Enter number: ");
    scanf("%d", &num);

    printf("Enter starting position: ");
    scanf("%d", &pos);

    printf("Enter number of bits to toggle: ");
    scanf("%d", &n);

    // creating mask
    mask = ((1 << n) - 1) << pos;

    // toggle bits
    result = num ^ mask;

    printf("Number after toggling bits = %d", result);

    return 0;
}