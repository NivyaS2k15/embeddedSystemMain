#include <stdio.h>

int sum(int arry[],int length)

{     int total=0;
    for (int i = 0; i <length; i++)
    {
        total+= arry[i];
    }
    printf("array sum is array %d\n", total);
}


void oddNumberPrint(int arry[],int length){
printf("odd numbers are:\n");
 for(int i=0;i<length;i++){
   if(arry[i]%2!=0){
    printf("%d\n",arry[i]);
   }
 }
}

void arrayForOddNumber(int arry[],int length){
    int count=0;
    int num2[length];
   
    for(int i=0;i<length;i++){
        if(arry[i]%2!=0){
        num2[count]= arry[i];
          count++;
        }
    }
    printf("new array which has odd number is :\n");
    for (int i=0;i<count;i++){
        printf("array[%d] value %d\n", i ,num2[i]);
    }
}

int main()
{
    int numberArr[] = {1, 2, 3, 4, 5, 6,7,8,9,10,11,12,13};
    int select;
    int size = sizeof(numberArr) / sizeof(numberArr[0]);
    printf("enter  number to select the function\n1)sum of array value\n2)odd number print\n3)print new array which has odd number only\n");
    scanf("%d",&select);
    if(select==1){
         sum(numberArr,size);

    }else if (select==2)
    {
      oddNumberPrint(numberArr,size);
    }else if (select==3)
    {
      arrayForOddNumber(numberArr,size);
        
    }else
        printf("you have selected wrong number");
    
    
    
   

    return 0;
}