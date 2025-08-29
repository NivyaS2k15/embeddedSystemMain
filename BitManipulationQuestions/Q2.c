#include<stdio.h>
//Q 2.)  Set the ith bit of a number.
int SetKBit(int num, int pos){
     int mask=1<<pos-1;
     return num|mask;

 }
int main()
{
     int num, pos;
    printf("enter the number");
    scanf("%d", &num);

    printf("enter the position");
    scanf("%d", &pos);
   int a = SetKBit(num, pos);
   printf("answer is : %d",a);
    return 0;
}