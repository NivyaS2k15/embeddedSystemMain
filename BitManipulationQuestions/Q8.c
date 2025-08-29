//Q 8.) Check if a number is power of 8
#include <stdio.h>
#include <stdbool.h>

// Check if n is a power of 8
bool checkPowerOf8(unsigned int n) {
    return (n != 0) && !(n & (n - 1)) && (n % 7 == 1);
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);

    if (checkPowerOf8(n)) {
        printf("The number %u is a power of 8\n", n);
    } else {
        printf("The number %u is NOT a power of 8\n", n);
    }

    return 0;
}
