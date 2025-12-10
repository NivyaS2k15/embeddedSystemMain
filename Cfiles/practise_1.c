#include <stdio.h>  
int main() {   //main function  
    int arr[5] = {10, 20, 30, 40, 50};  
    int (*ptr)[5] ;
    ptr = arr;   
    int *pt = arr; 
    printf("First element: %d\n", (ptr)[0]);  
    printf("First element pt address: %x\n", (pt));
    printf("second address: %x\n", (ptr)[1]); 
      printf("second element pt address: %x\n", (pt+1));
       printf("third address: %x\n", (ptr)[2]); 
    
  
    printf("third element pt address: %x\n", (pt+2));
      printf("fourth address: %x\n", (ptr)[3]); 
    
  
    printf("fourth element pt address: %x\n", (pt+3));
     printf("First element: %d\n", (*ptr)[0]); 
        printf("First element pt : %d\n", *(pt)); 
    printf("second address: %d\n", (*ptr)[1]); 
       printf("second element pt : %d\n", *(pt+1));
       printf("third address: %d\n", (*ptr)[2]); 
     
 
    printf("third element pt  %d\n", *(pt+2));
    return 0;  
}  