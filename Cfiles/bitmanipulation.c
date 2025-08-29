#include <stdio.h>

void PrintBin(int n){
int i,mask;
for (i=31;i>=0;i--){
   mask = 1<<i;
    if(n & mask)
    printf("1");
    else
    printf("0");
}
printf("\n");
}

void setbit(int n,int pos){
int mask;
mask= 1<<pos;
n=n|mask;
printf("after setting the position in %d ",pos);
PrintBin(n);

}
void clearBit(int n,int pos){
  int mask;
  mask = 1<<pos;
  n= n & (~mask);
  printf("after setting the postion in %d",pos);
  PrintBin(n);



  
}
int main(){
    int a,c,s;
    printf("Enter a number:");
    scanf("%d",&a);
    PrintBin(a);
    printf("enter the position to set the bit");
    scanf("%d",&s);
    setbit(a,s);
    printf("Enter the position to the clear the bit");
    scanf("%d",&c);
    clearBit(a,c);


    return 0;
}