#include <stdio.h>

int main() {
    int n;
    int i;
    unsigned long long f = 1;

   
    printf("Enter a positive integer: ");
    scanf("%d", &n);

   
    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        for (i = 1; i <= n; i++) {
            f *= i; 
        }
        printf("Factorial of %d = %llu\n", n, f);
    }

    return 0;
}
