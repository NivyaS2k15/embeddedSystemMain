#include <stdio.h>

int main() {
    int a = 7;        // integer
    double b = 2.5;   // double

    // Implicit type casting: int is promoted to double before division
    float result = a / b;  

    printf("a = %d\n", a);
    printf("b = %f\n", b);
    printf("Result (implicit cast) = %f\n", result);


    //explicit type casting
    int num1,num2;
    printf("enter two integer");
    scanf("%d %d",&num1,&num2);
    float result2 = (float) num1/num2; // explicitally type casting here to avoid the truncate to save decimal values
    
    printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);
    printf("Result (explicit cast) = %f\n", result2);

    return 0;
}
