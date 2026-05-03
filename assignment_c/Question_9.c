#include <stdio.h>


float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 0;
    }
    return a / b;
}


float evaluate(float a, float b, char op) {
    switch (op) {
        case '+': return add(a, b);
        case '-': return subtract(a, b);
        case '*': return multiply(a, b);
        case '/': return divide(a, b);
        default:
            printf("Error: Invalid operator '%c'.\n", op);
            return 0;
    }
}

int main() {
    float num1, num2, result;
    char op;

    
    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &op); 

    printf("Enter second number: ");
    scanf("%f", &num2);

 
    result = evaluate(num1, num2, op);

  
    printf("Result: %.2f %c %.2f = %.2f\n", num1, op, num2, result);

    return 0;
}
