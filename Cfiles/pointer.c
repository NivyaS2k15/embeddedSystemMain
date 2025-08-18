#include <stdio.h>
int main(){

 int a =10;
 int b=20;
 int *p=&a;
 int *q=&b;
printf("value of a %d\n",a);
printf("value of &a is %p\n",&a);
printf("value of p is %p\n",p);
printf("value of address of p is %p\n",&p);
printf("value of *p is%d\n",*p);
printf("value of b %d\n",b);
printf("value of &b is %p\n",&b);
printf("value of p is %p\n",p);
printf("value of q is %p\n",q);
printf("value of *q is%d\n",*q);
printf("value of address of q is %p\n",&q);
    return 0;
}