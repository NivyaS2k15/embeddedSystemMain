#include <stdio.h>

// Function to modify the register
unsigned char modifyRegister(unsigned char reg) {
    reg |=  (1 << 2);   // Set 3rd bit (bit index 2)
    reg &= ~(1 << 5);   // Clear 6th bit (bit index 5)
    reg ^=  (1 << 0);   // Toggle 1st bit (bit index 0)
    return reg;
}

// Function to print binary (for visualization only)
void printBinary(unsigned char n) {
    printf("0b");
    printf("%d%d%d%d%d%d%d%d",
        (n >> 7) & 1,
        (n >> 6) & 1,
        (n >> 5) & 1,
        (n >> 4) & 1,
        (n >> 3) & 1,
        (n >> 2) & 1,
        (n >> 1) & 1,
        (n >> 0) & 1
    );
    printf("\n");
}

int main() {
    unsigned char reg = 245; // Example: 0b11110101
    unsigned char result = modifyRegister(reg);

    printf("Input  : ");
    printBinary(reg);
    printf("Output : ");
    printBinary(result);

    return 0;
}