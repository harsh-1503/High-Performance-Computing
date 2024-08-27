#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void sort(int *arr, int n, int isA)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((isA && arr[i] > arr[j]) || (!isA && arr[i] < arr[j]))
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    int n = 5;
    int a[] = {1, 3, -5, 7, 9};
    int b[] = {2, -6, 4, -8, 10};
    int result = 0;

    // Sort arrays in sequential order
    sort(a, n, 1); // Sort `a` in ascending order
    sort(b, n, 0); // Sort `b` in descending order

// Parallel loop to calculate the minimum scalar product
#pragma omp parallel for reduction(+ : result) schedule(static, 2)
    for (int i = 0; i < n; i++)
    {
        result += a[i] * b[i];
    }

    printf("Minimum Scalar Product: %d\n", result);
    return 0;
}
