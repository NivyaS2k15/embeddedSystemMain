#include <stdio.h>

int main() {
    int arr[100], size, i, j, k;

    // Input size
    printf("Enter size of array: ");
    scanf("%d", &size);

    // Input elements
    printf("Enter %d elements:\n", size);
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Remove duplicates
    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                // Shift elements left
                for(k = j; k < size - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                size--;   // reduce size
                j--;      // check again at same position
            }
        }
    }

    // Print result
    printf("Array after removing duplicates:\n");
    for(i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
