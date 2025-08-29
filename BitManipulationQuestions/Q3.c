#include<stdio.h>
//Q 3.) clear the ith bit of a number
int ClearBit(int num, int pos){
     int mask=1<<pos-1;
     return num & (~mask);

 }
int main()
{
     int num, pos;
    printf("enter the number");
    scanf("%d", &num);

    printf("enter the position");
    scanf("%d", &pos);
   int a = ClearBit(num, pos);
    printf("answer is : %d ",a);
    return 0;
}