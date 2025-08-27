#include<stdio.h>
#pragma pack(1)
   struct k{
         char x : 1;
         char y : 7;
         int z : 8;
    };
int main(){
    printf("\nSize of structure k = %d", sizeof(struct k));
return 0;
    }