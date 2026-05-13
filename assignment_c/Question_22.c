#include <stdio.h>

int main() {
    int arr[100], size, i;
    int largest, secondLargest, smallest, secondSmallest;

    printf("Enter size of array: ");
    scanf("%d", &size);

    if(size < 2) {
        printf("Need at least 2 elements.\n");
        return 0;
    }

    printf("Enter %d elements:\n", size);
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // initialize
    largest = smallest = arr[0];
    for(i = 1; i < size; i++) {
        if(arr[i] > largest) {
            largest = arr[i];
        }
        if(arr[i] < smallest) {
            smallest = arr[i];
        }
    }

    // set defaults
    secondLargest = smallest;
    secondSmallest = largest;

    for(i = 0; i < size; i++) {
        if(arr[i] > secondLargest && arr[i] < largest) {
            secondLargest = arr[i];
        }
        if(arr[i] < secondSmallest && arr[i] > smallest) {
            secondSmallest = arr[i];
        }
    }

    if(largest == smallest) {
        printf("All elements are equal. No second largest or smallest.\n");
    } else {
        printf("Second Largest = %d\n", secondLargest);
        printf("Second Smallest = %d\n", secondSmallest);
    }

    return 0;
}
