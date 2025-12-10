
#include <stdio.h>  
void add(void) {  
    printf("everything is fine \n"); 
}  
int main() {  //main function  
    void (*funcPtr)(void);    
    funcPtr = &add;         // same as funcPtr= add; s       
    funcPtr();   
     funcPtr(); 
    return 0;  
}