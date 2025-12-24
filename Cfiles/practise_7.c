#include <stdio.h>  
int main()  
{  
   int a=90;  
   void *ptr;  
   ptr=&a; 
   char ch ='c';
   int b=7;
   void * p = &b;
   printf("the address stored in the p is %p\n",(int*)p);
         printf("the address of the b is %p\n",&b);

      printf("the address of the p is %p\n",&p);

   printf("Value which is pointed by ptr pointer : %d\n",*(int*)ptr); 
   printf("the address of ch is %p",&ch); 
   return 0;  
}  