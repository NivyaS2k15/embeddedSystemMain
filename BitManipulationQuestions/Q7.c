//Q 7.) Check if a number is a power of 4
#include <stdio.h>
#include <stdbool.h>

// Check if n is a power of 4 using bitwise and modulo logic
bool checkPowerOf4(unsigned int n) {
    // First, check if n is a power of 2
    // Then, check if it satisfies the modulo condition for power of 4
    return (n != 0) && !(n & (n - 1)) && (n % 3 == 1);
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);

    if (checkPowerOf4(n)) {
        printf("The number %u is a power of 4\n", n);
    } else {
        printf("The number %u is NOT a power of 4\n", n);
    }

    return 0;
}