#include <stdio.h>
// Q 6.) Check if the number is a power of 2?

int powerOF2(int n){
    return (!(n & n-1));
}

void checkPowerof2(int n){
   
    
   int result = powerOF2(n);
   if(result){
    printf("the number %d    power of 2 ",n);
   }
   else
   {
        printf("the number %d is not a  power of 2 ",n);

   }
}
int main (){
    int n;
    printf("enter the number");
    scanf("%d", &n);
    checkPowerof2( n);

    

    
    return 0;

}