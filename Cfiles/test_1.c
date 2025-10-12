#include <stdio.h>

int findSecondLargest(int arr[], int size) {
    int largest, secondLargest;

    // Initialize with first two elements
    if (arr[0] > arr[1]) {
        largest = arr[0];
        secondLargest = arr[1];
    } else {
        largest = arr[1];
        secondLargest = arr[0];
    }

    for (int i = 2; i < size; i++) {
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] > secondLargest && arr[i] != largest) {
            secondLargest = arr[i];
        }
    }

    return secondLargest;
}

// Example usage
int main() {
    int arr[] = {12, 45, 1, 34, 45, 23};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findSecondLargest(arr, size);
    printf("Second largest element: %d\n", result);

    return 0;
}