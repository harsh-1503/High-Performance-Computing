#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    int threads = 64;
    int iterations = 1e9;

    while (threads > 0)
    {
        double pi_estimate = 0.0;
        omp_set_num_threads(threads);
        double begin_time = omp_get_wtime();
        int total_count = 0;

#pragma omp parallel
        {
            unsigned int thread_seed = (unsigned int)time(NULL) ^ omp_get_thread_num();
            srand(thread_seed); // Seed the random number generator
            int local_hits = 0;

#pragma omp for
            for (int iter = 0; iter < iterations; iter++)
            {
                double x_val = (double)rand() / RAND_MAX;
                double y_val = (double)rand() / RAND_MAX;
                if (x_val * x_val + y_val * y_val <= 1.0)
                    local_hits++;
            }

#pragma omp atomic
            total_count += local_hits;
        }

        pi_estimate = 4.0 * (double)total_count / (double)iterations;
        double finish_time = omp_get_wtime();
        // printf("Calculated Pi: %f\n", pi_estimate);
        printf("%f seconds for %d threads\n", finish_time - begin_time, threads);

        threads /= 2;
    }

    double serial_begin = omp_get_wtime();
    int serial_count = 0;
    unsigned int serial_seed = (unsigned int)time(NULL);
    srand(serial_seed); // Seed the random number generator

    for (int serial_iter = 0; serial_iter < iterations; serial_iter++)
    {
        double serial_x = (double)rand() / RAND_MAX;
        double serial_y = (double)rand() / RAND_MAX;
        if (serial_x * serial_x + serial_y * serial_y <= 1.0)
            serial_count++;
    }

    double pi_final = 4.0 * (double)serial_count / (double)iterations;
    double serial_finish = omp_get_wtime();

    printf("Time taken for sequential execution: %f seconds\n", serial_finish - serial_begin);
    printf("Calculated Pi: %f\n", pi_final);

    return 0;
}
