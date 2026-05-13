#include <stdio.h>

// define structure
struct Complex {
    float real;
    float imag;
};

// function to add two complex numbers
struct Complex add(struct Complex c1, struct Complex c2) {
    struct Complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}

// function to display a complex number
void display(struct Complex c) {
    printf("%.2f + %.2fi\n", c.real, c.imag);
}

int main() {
    struct Complex num1, num2, sum;

    // input first complex number
    printf("Enter real part of first complex number: ");
    scanf("%f", &num1.real);
    printf("Enter imaginary part of first complex number: ");
    scanf("%f", &num1.imag);

    // input second complex number
    printf("Enter real part of second complex number: ");
    scanf("%f", &num2.real);
    printf("Enter imaginary part of second complex number: ");
    scanf("%f", &num2.imag);

    // add them
    sum = add(num1, num2);

    // display result
    printf("Sum of complex numbers: ");
    display(sum);

    return 0;
}
