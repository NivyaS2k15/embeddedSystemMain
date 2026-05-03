#include <stdio.h>

int main() {
    int number;

   
    printf("Enter an integer: ");
    scanf("%d", &number);

    // Check divisibility by 2
    if (number % 2 == 0) {
        printf("%d is even.\n", number);
    } else {
        printf("%d is odd.\n", number);
    }

    return 0;
}
