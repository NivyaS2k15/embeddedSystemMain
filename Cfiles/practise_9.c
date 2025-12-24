#include <stdio.h>  
int square( void* num) {  
   *( int*)num =10;
    return   *(const int*)num ;
}  
int main() {   //main function  
    int n = 9;  
        printf("Square of %d is \n", n);  

    int sq = square(&n);  
    printf("Square of %d is %d\n", n, sq);  
    return 0;  
}