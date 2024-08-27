#include <stdio.h>
#include <omp.h>

int main()
{
    int vec_size, add_value, total_threads;

    printf("Enter the size of the vector: ");
    scanf("%d", &vec_size);

    printf("Enter the scalar value to add: ");
    scanf("%d", &add_value);

    printf("Enter the number of threads: ");
    scanf("%d", &total_threads);

    int arr[vec_size];
    for (int idx = 0; idx < vec_size; idx++)
        arr[idx] = idx + 1;

    omp_set_num_threads(total_threads);

#pragma omp parallel for
    for (int idx = 0; idx < vec_size; idx++)
    {
        printf("Thread %d: Adding %d to %d\n", omp_get_thread_num(), add_value, arr[idx]);
        arr[idx] += add_value;
    }

    printf("Resultant vector:\n");
    for (int idx = 0; idx < vec_size; idx++)
    {
        printf("%d ", arr[idx]);
    }
    printf("\n");

    return 0;
}
