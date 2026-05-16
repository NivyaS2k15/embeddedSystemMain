#include <stdio.h>

// Structure for complex number
struct Complex
{
    float real;
    float imag;
};

// Function to add two complex numbers
struct Complex addComplex(struct Complex c1, struct Complex c2)
{
    struct Complex result;

    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;

    return result;
}

// Function to display complex number
void displayComplex(struct Complex c)
{
    printf("Result = %.2f + %.2fi\n", c.real, c.imag);
}

int main()
{
    struct Complex num1, num2, sum;

    // Input first complex number
    printf("Enter real part of first complex number: ");
    scanf("%f", &num1.real);

    printf("Enter imaginary part of first complex number: ");
    scanf("%f", &num1.imag);

    // Input second complex number
    printf("Enter real part of second complex number: ");
    scanf("%f", &num2.real);

    printf("Enter imaginary part of second complex number: ");
    scanf("%f", &num2.imag);

    // Add complex numbers
    sum = addComplex(num1, num2);

    // Display result
    displayComplex(sum);

    return 0;
}