#include <stdio.h>


int functtionReg(int reg) {
    reg |=  (1 << 2);  
    reg &= ~(1 << 5);  
    reg ^=  (1 << 0);  
    return reg;
}

void printBinary (int n){
int i,mask;
for (i=7;i>=0;i--){
   mask = 1<<i;
    if(n & mask)
    printf("1");
    else
    printf("0");
}
printf("\n");
}

int main() {
    int reg = 245;   
    int result = functtionReg(reg);

  
    printf("binary Input  : ");
    printBinary(reg);
    printf("ibnary Output : ");
    printBinary(result);

    return 0;
}
