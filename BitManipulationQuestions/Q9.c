//Q 9.) Check if a number is a power of 16

#include <stdio.h>
#include <stdbool.h>

// Check if n is a power of 16
bool checkPowerOf16(unsigned int n) {
    return (n != 0) && !(n & (n - 1)) && (n % 15 == 1);
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);

    if (checkPowerOf16(n)) {
        printf("The number %u is a power of 16\n", n);
    } else {
        printf("The number %u is NOT a power of 16\n", n);
    }

    return 0;
}