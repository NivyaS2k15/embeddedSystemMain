//Q 10.) Toggle ith Bit of a number



#include <stdio.h>

void printBin(int n)
{

    for (int i = 31; i >= 0; i--)
    {

        if (n & (1 << i))
            printf("1");
        else
            printf("0");
    }
}
int ToggleIthBit(int n,int pos){
    int mask = 1<<(pos-1);
  n=  n ^  mask;
  printf("\n");

  printBin(n);

}
int main()
{

    int n,pos;
    printf("enter the number");
    scanf("%d", &n);
      printf("enter the pos");
    scanf("%d", &pos);
    printBin(n);
    ToggleIthBit(n,pos);
    return 0;
}