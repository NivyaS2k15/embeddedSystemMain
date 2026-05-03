#include <stdio.h>

int main() {
    int n, i;
   int  isprime = 1;

    printf("Enter an integer: ");
    scanf("%d", &n);

   
    if (n <= 1) {
        printf("%d is not a prime number.\n", n);
        return 0;
    }

    
    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            isprime = 0; 
            break;
        }
    }

  
    if (isprime) {
        printf("%d is a prime number.\n", n);
    } else {
        printf("%d is not a prime number.\n", n);
    }

    return 0;
}
