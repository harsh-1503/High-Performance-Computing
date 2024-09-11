#include <stdio.h>
#include <omp.h>

int main()
{
    long long total_sum = 0;
    int n = 20000000; // First 20 natural numbers
    long long partial_sum = 0;

    // Start measuring time
    double start_time = omp_get_wtime();

#pragma omp parallel for reduction(+ : total_sum) lastprivate(partial_sum)
    for (int i = 1; i <= n; i++)
    {
        partial_sum += i;
        total_sum += i;
    }

    // Stop measuring time
    double end_time = omp_get_wtime();

    printf("Final total sum of the first %d natural numbers is: %d\n", n, total_sum);
    printf("Execution time: %f seconds\n", end_time - start_time);

    return 0;
}