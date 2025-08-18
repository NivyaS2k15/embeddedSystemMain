#include <stdio.h>

int main()
{
    int arr[5];
    int *p1 = &arr[0];
    int *p2 = &arr[1];
    int *p3 = &arr[2];
    int *p4 = &arr[3];
    int *p5 = &arr[4];
    int *p6 = &arr[5];
    int *p7 = &arr[6];
    printf("the address of arr[0] : %p\n", &arr[0]);
    printf("the value of p1: %p\n  ", p1);
    printf("the value of adrress  &p1 is  %p\n ", &p1);
    printf("the address of arr[1] : %p\n", &arr[1]);
    printf("the value of p2%p\n", p2);
    printf("the value of adrress  &p2 is : %p\n", &p2);
    printf("the address of arr[2] : %p\n", &arr[2]);
    printf("the value of p3 : %p\n", p3);
    printf("the value of adrress  &p3 is : %p\n", &p3);
    printf("the address of arr[3] : %p\n", &arr[3]);
    printf("the value of p4: %p\n  ", p4);
    printf("the value of adrress  &p4 is  %p\n ", &p4);
    printf("the address of arr[4] : %p\n", &arr[4]);
    printf("the value of p5: %p\n  ", p5);
    printf("the value of adrress  &p5 is  %p\n ", &p5);
    printf("the address of arr[5] : %p\n", &arr[5]);
    printf("the value of p6: %p\n  ", p6);
    printf("the value of adrress  &p6 is  %p\n ", &p6);
    printf("the address of arr[6] : %p\n", &arr[6]);
    printf("the value of p7: %p\n  ", p7);
    printf("the value of adrress  &p7 is  %p\n ", &p7);
    return 0;
}
