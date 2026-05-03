#include <stdio.h>

// Function to count digit frequency
void countFrequency(int num, int freq[]) {
    int digit;

    // Handle case when number is 0
    if (num == 0) {
        freq[0]++;
        return;
    }

    // If number is negative, make it positive
    if (num < 0) {
        num = -num;
    }

    // Extract digits and update frequency
    while (num > 0) {
        digit = num % 10;   // get last digit
        freq[digit]++;      // increment count
        num = num / 10;     // remove last digit
    }
}

int main() {
    int num;
    int freq[10] = {0};  // initialize all frequencies to 0

    printf("Enter an integer: ");
    scanf("%d", &num);

    // Call function (array passed by reference)
    countFrequency(num, freq);

    // Print results
    printf("\nDigit Frequencies:\n");
    for (int i = 0; i < 10; i++) {
        printf("Digit %d: %d times\n", i, freq[i]);
    }

    return 0;
}