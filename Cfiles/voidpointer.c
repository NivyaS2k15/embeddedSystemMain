#include <stdio.h>
int main(){
    int a =10;
   
 void *p = &a;
 float arr[5];
 void *ptr = arr;
    printf("value of %d\n",*(int*)p);
     a=30;
     printf("value of %d\n",*(int*)p);
     *(int*)p=40;
      printf("value of %d\n",*(int*)p);
   
    printf("enter the element");
    for(int i=0;i<5;i++){
     scanf("%f",(float*)ptr+i );

    }
for(int i=0;i<5;i++){
  printf("the element of index %d is %f\n",i,*((float*)ptr+i));
  printf("%p\n",ptr+i);
}
 return 0;
}