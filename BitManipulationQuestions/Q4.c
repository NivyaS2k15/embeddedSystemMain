#include <stdio.h>
//Q 4.) Remove the last set bit of a number

int rightmostSetBitPos(unsigned int n) {
    if (n == 0) return 0; // No set bits
    int value = n &(n-1);
    return value;
}

int main(){
    int n;
    printf("enter the number");
    scanf("%d",&n);

   int a =rightmostSetBitPos(n);
   printf("the answer %d",a);


    return 0;
}