#include <stdio.h>

int main() {
    int arr1[100], arr2[100], arr3[200];
    int size1, size2, size3;
    int i, j, k;

    printf("Enter size of first array: ");
    scanf("%d", &size1);

    printf("Enter %d elements (sorted ascending):\n", size1);
    for(i = 0; i < size1; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter size of second array: ");
    scanf("%d", &size2);

    printf("Enter %d elements (sorted ascending):\n", size2);
    for(i = 0; i < size2; i++) {
        scanf("%d", &arr2[i]);
    }

    // merge process
    i = 0; j = 0; k = 0;
    while(i < size1 && j < size2) {
        if(arr1[i] < arr2[j]) {
            arr3[k] = arr1[i];
            i++;
        } else {
            arr3[k] = arr2[j];
            j++;
        }
        k++;
    }

    // copy remaining elements
    while(i < size1) {
        arr3[k] = arr1[i];
        i++;
        k++;
    }
    while(j < size2) {
        arr3[k] = arr2[j];
        j++;
        k++;
    }

    size3 = k;

    printf("Merged sorted array:\n");
    for(i = 0; i < size3; i++) {
        printf("%d ", arr3[i]);
    }

    return 0;
}
