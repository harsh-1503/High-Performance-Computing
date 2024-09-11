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

    double start_time_serial = omp_get_wtime();

    for (int idx = 0; idx < vec_size; idx++)
    {
        arr[idx] = idx + 1;
        arr[idx] += add_value;
    }

    double end_time_serial = omp_get_wtime();
    double serial_time = end_time_serial - start_time_serial;

    omp_set_num_threads(total_threads);

    double start_time_parallel = omp_get_wtime();

#pragma omp parallel for
    for (int idx = 0; idx < vec_size; idx++)
    {
        arr[idx] = idx + 1;
        arr[idx] += add_value;
    }

    double end_time_parallel = omp_get_wtime();
    double parallel_time = end_time_parallel - start_time_parallel;

    printf("Serial Execution Time: %f seconds\n", serial_time);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    double speedup = serial_time / parallel_time;
    printf("Speedup: %f\n", speedup);
    printf("Hello World!!");
    printf("Resultant vector:\n");
    // for (int idx = 0; idx < vec_size; idx++)
    // {
    //     printf("%d ", arr[idx]);
    // }
    // printf("\n");

    return 0;
}
