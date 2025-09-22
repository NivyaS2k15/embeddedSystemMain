#include <stdio.h>

int findSecondLargest(int arr[], int size) {

    int first, second;

  
    
        first = arr[0];
        second = arr[1];

    for (int i = 2; i < size; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }

    return second;
}

int main() {
    int n;
    printf("enter  n");
    scanf("%d", &n);
    int arr[n];
    printf("enter array\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = findSecondLargest(arr, n);
    printf("Second largest element: %d\n", result);


    return 0;
}