#include <stdio.h>    
   int add(float x,int y)    
{    
    int a=x+y;    
    return a;    
}    
int sub(float x,int y)    
{    
    int a=x-y;    
    return a;    
}    
int mul(float x,int y)    
{    
    int a=x*y;    
    return a;    
}    
int div(float x,int y)    
{    
    int a=x/y;    
    return a;    
}    
int main()    //main function  
{    
    float x;      // variable declaration.    
    int y;    
    int (*fp[4]) (float,int);        // function pointer declaration.    
    fp[0]=add;     // assigning addresses to the elements of an array of a function pointer.    
    fp[1]=sub;    
    fp[2]=mul;    
    fp[3]=div;    
    printf("Enter the values of x and y : ");    
    scanf("%f %d",&x,&y);    
  int r=(fp[0]) (x,y);        // Calling add() function.    
    printf("\nSum of two values is : %d",r);    
     r=(fp[1]) (x,y);             // Calling sub() function.    
    printf("\nDifference of two values is : %d",r);    
      r=(fp[2]) (x,y);            // Calliung sub() function.    
    printf("\nMultiplication of two values is : %d",r);    
     r=(fp[3]) (x,y);           // Calling div() function.    
    printf("\nDivision of two values is : %d",r);    
    return 0;    
}    
    
 