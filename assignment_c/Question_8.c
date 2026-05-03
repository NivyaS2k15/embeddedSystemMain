#include <stdio.h>

// Function to convert decimal to given base
void convertToBase(int num, int base, char result[]) {
    char digits[] = "0123456789ABCDEF"; // For bases up to 16
    int index = 0;

    // Special case: if number is 0
    if (num == 0) {
        result[index++] = '0';
        result[index] = '\0';
        return;
    }

    // Repeated division method
    while (num > 0) {
        int remainder = num % base;
        result[index++] = digits[remainder]; // Store remainder as character
        num /= base;
    }

    result[index] = '\0';

    // Reverse the result string (since digits are stored backwards)
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
}

int main() {
    int number, base;
    char result[65]; // Enough to hold binary representation of 64-bit number

    // Prompt the user
    printf("Enter a decimal number: ");
    scanf("%d", &number);

    printf("Enter target base (2–16): ");
    scanf("%d", &base);

    if (base < 2 || base > 16) {
        printf("Base must be between 2 and 16.\n");
    } else {
        convertToBase(number, base, result);
        printf("Number %d in base %d is: %s\n", number, base, result);
    }

    return 0;
}
