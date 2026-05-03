#include <stdio.h>


int stringToInteger(char str[]) {
    int result = 0;

    for (int i = 0; str[i] != '\0'; i++) {
       
        int digit = str[i] - '0';
        result = result * 10 + digit; 
    }

    return result;
}

int main() {
    char str[100];
    int number;

   
    printf("Enter a number as a string: ");
    scanf("%s", str);

    
    number = stringToInteger(str);

    
    printf("The integer value is: %d\n", number);

    return 0;
}
