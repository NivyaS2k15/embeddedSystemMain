#include <stdio.h>

// Recursive function to find GCD
int gcd(int a, int b) {
    if (b == 0) {
        return a; // Base case: when remainder is 0
    }
    return gcd(b, a % b); // Recursive step
}

int main() {
    int num1, num2;

    // Prompt the user
    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);

    if (num1 <= 0 || num2 <= 0) {
        printf("Please enter positive integers only.\n");
    } else {
        printf("GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));
    }

    return 0;
}
