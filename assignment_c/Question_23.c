#include <stdio.h>

int main() {
    int arr[100], size, i, n, dir;
    int temp[100];

    printf("Enter size of array: ");
    scanf("%d", &size);

    printf("Enter %d elements:\n", size);
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter number of positions to rotate: ");
    scanf("%d", &n);

    printf("Enter direction (1 for left, 2 for right): ");
    scanf("%d", &dir);

    // handle n larger than size
    n = n % size;

    if(dir == 1) {
        // left rotation
        for(i = 0; i < size; i++) {
            temp[i] = arr[(i + n) % size];
        }
    } else {
        // right rotation
        for(i = 0; i < size; i++) {
            temp[i] = arr[(i - n + size) % size];
        }
    }

    printf("Array after rotation:\n");
    for(i = 0; i < size; i++) {
        printf("%d ", temp[i]);
    }

    return 0;
}
