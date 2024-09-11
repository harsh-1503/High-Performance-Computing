#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 100000000 // Size of the array

// Function to initialize the array with random values
void initializeArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100; // Initialize with random values
    }
}

// Sequential version to calculate the sum of all elements in the array
long long sequentialSum(int *array, int size)
{
    long long sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }
    return sum;
}

// Parallel version to calculate the sum using OpenMP with reduction clause
long long parallelSum(int *array, int size)
{
    long long sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }

    return sum;
}

int main()
{
    // Allocate memory for the array
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    initializeArray(array, ARRAY_SIZE);

    // Sequential sum calculation
    double start_time = omp_get_wtime();
    long long seq_sum = sequentialSum(array, ARRAY_SIZE);
    double end_time = omp_get_wtime();
    double seq_time = end_time - start_time;

    printf("Sequential sum: %lld\n", seq_sum);
    printf("Sequential execution time: %f seconds\n", seq_time);

    // Parallel sum calculation
    start_time = omp_get_wtime();
    long long par_sum = parallelSum(array, ARRAY_SIZE);
    end_time = omp_get_wtime();
    double par_time = end_time - start_time;

    printf("Parallel sum: %lld\n", par_sum);
    printf("Parallel execution time: %f seconds\n", par_time);

    // Performance analysis
    printf("Performance analysis:\n");
    printf("Speedup: %f\n", seq_time / par_time);
    printf("Efficiency: %f%%\n", (seq_time / par_time) * 100 / omp_get_max_threads());

    // Cleanup
    free(array);

    return 0;
}
