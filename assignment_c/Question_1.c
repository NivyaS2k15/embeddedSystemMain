#include <stdio.h>

int main() {
    int n;

   
    printf("Enter an integer: ");
    scanf("%d", &n);

    // Check divisibility by 2
    if (n % 2 == 0) {
        printf("%d is even.\n", n);
    } else {
        printf("%d is odd.\n", n);
    }

    return 0;
}
