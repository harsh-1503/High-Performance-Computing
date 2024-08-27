#include <stdio.h>
#include <omp.h>

int main(void)
{
    int num_threads = 0;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    double start_time = omp_get_wtime();
    printf("\nSequential printing:\n");
    for (int i = 0; i < num_threads; i++)
    {
        printf("Hello, World\n");
    }
    double end_time = omp_get_wtime();

    printf("TIME FOR SEQUENTIAL PRINTING: %f\n", end_time - start_time);

    omp_set_num_threads(num_threads);
    printf("\nParallel printing:\n");
    start_time = omp_get_wtime();
#pragma omp parallel
    {
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }

    end_time = omp_get_wtime();

    printf("TIME FOR Parallel PRINTING: %f\n", end_time - start_time);

    return 0;
}