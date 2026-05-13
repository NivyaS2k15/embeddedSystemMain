#include <stdio.h>

int main()
{
    int n, i;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int a[n], result[n];

    printf("Enter array elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int k = 0;

    // first store all negative numbers
    for(i = 0; i < n; i++)
    {
        if(a[i] < 0)
        {
            result[k] = a[i];
            k++;
        }
    }

    // then store all positive numbers (including zero)
    for(i = 0; i < n; i++)
    {
        if(a[i] >= 0)
        {
            result[k] = a[i];
            k++;
        }
    }

    printf("Rearranged array:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d ", result[i]);
    }

    return 0;
}