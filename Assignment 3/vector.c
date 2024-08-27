#include <stdio.h>
#include <omp.h>

void add_scalar_static(int arr[], int len, int value, int block_size, int thread_count) {
    omp_set_num_threads(thread_count);
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static, block_size)
    for (int idx = 0; idx < len; idx++) {
        arr[idx] += value;
    }

    double end = omp_get_wtime();
    printf("STATIC - Block Size: %d, Threads: %d, Time: %f seconds\n", block_size, thread_count, end - start);
}

void add_scalar_dynamic(int arr[], int len, int value, int block_size, int thread_count) {
    omp_set_num_threads(thread_count);
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, block_size)
    for (int idx = 0; idx < len; idx++) {
        arr[idx] += value;
    }

    double end = omp_get_wtime();
    printf("DYNAMIC - Block Size: %d, Threads: %d, Time: %f seconds\n", block_size, thread_count, end - start);
}

void add_scalar_nowait(int arr[], int len, int value, int thread_count) {
    omp_set_num_threads(thread_count);
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 4) nowait
        for (int idx = 0; idx < len; idx++) {
            arr[idx] += value;
        }
    }

    double end = omp_get_wtime();
    printf("NOWAIT - Threads: %d, Time: %f seconds\n", thread_count, end - start);
}

int main() {
    int len = 200;
    int arr[len];
    int value = 5;
    
    for (int idx = 0; idx < len; idx++) {
        arr[idx] = idx;
    }

    int thread_options[] = {2, 4, 8};
    int block_sizes[] = {1, 2, 4, 8};

    // Testing STATIC schedule
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            // Reset array
            for (int k = 0; k < len; k++) {
                arr[k] = k;
            }
            add_scalar_static(arr, len, value, block_sizes[j], thread_options[i]);
        }
    }

    // Testing DYNAMIC schedule
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            // Reset array
            for (int k = 0; k < len; k++) {
                arr[k] = k;
            }
            add_scalar_dynamic(arr, len, value, block_sizes[j], thread_options[i]);
        }
    }

    // Demonstrate the NOWAIT clause
    add_scalar_nowait(arr, len, value, 4);

    return 0;
}
