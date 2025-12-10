#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *ptr = 560;
    printf("the pointer is %p\n", ptr); 
    printf("the pointer is %d\n", *ptr);

    free(ptr);  // now safe
     ptr = NULL;
    printf("the pointer is  cc %p\n", ptr); //garbage print due to the dangling pointer
    return 0;
}
