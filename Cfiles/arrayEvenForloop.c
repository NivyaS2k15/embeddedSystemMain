#include <stdio.h>
int main (){
    int a;
    int  j=0;
   int arr[10];
    for (int i=0;i<=10;i++){
        arr[i]= j;
       j= j+2;

        printf("arr[%d]=%d\n",i,arr[i]);

    }
    return 0;
}