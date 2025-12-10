#include <stdio.h>  
int main() {   //main function  
    int num = 100;  
    int *ptr1 = &num       ;
    int **ptr2 = &ptr1;      
    printf("Value of num: %d\n", num);  
    printf("Value using ptr1: %d\n", *ptr1);  
    printf("Value using ptr2: %d\n", **ptr2);  
     printf("Value address num: %p\n", &num);  // 6422296
    printf("Value address ptr1: %p\n", ptr1);  // 6422296
     printf("Value address &ptr1: %p\n", &ptr1);  //address of pointer variable
    printf("Value address *ptr2: %p\n", *ptr2);  //  6422296 adress of num
    printf("Value address ptr2: %p\n", ptr2);  //   adrress of ptr1
    printf("Value address &ptr2: %p\n", &ptr2);  //  
    return 0;  
}  