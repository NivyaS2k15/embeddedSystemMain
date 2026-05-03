#include <stdio.h>

// Function to check if a number is perfect
int isPerfect(int num) {
    int sum = 0;

    // Find divisors and add them
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }

    // Return 1 (true) if sum equals number, else 0 (false)
    return (sum == num);
}

int main() {
    int number;

    // Prompt the user
    printf("Enter a positive integer: ");
    scanf("%d", &number);

    if (number <= 0) {
        printf("Please enter a positive integer.\n");
    } else {
        if (isPerfect(number)) {
            printf("%d is a Perfect Number.\n", number);
        } else {
            printf("%d is not a Perfect Number.\n", number);
        }
    }

    return 0;
}
