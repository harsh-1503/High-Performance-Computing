#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_LIMIT 1024

void multiply_matrix_vector(double **M, double *V, double *R, int dim, int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int x = 0; x < dim; x++) {
        R[x] = 0.0;
        for (int y = 0; y < dim; y++) {
            R[x] += M[x][y] * V[y];
        }
    }
}

int main() {
    int dimensions[] = {512, 1024, 2048};
    int count_dim = sizeof(dimensions) / sizeof(dimensions[0]);
    int thread_set[] = {1, 2, 4, 8};
    int count_threads = sizeof(thread_set) / sizeof(thread_set[0]);

    for (int p = 0; p < count_dim; p++) {
        int dim = dimensions[p];
        printf("Size: %d x %d\n", dim, dim);

        double **M = (double **)malloc(dim * sizeof(double *));
        double *V = (double *)malloc(dim * sizeof(double));
        double *R = (double *)malloc(dim * sizeof(double));
        for (int x = 0; x < dim; x++) {
            M[x] = (double *)malloc(dim * sizeof(double));
        }

        for (int x = 0; x < dim; x++) {
            V[x] = rand() % 100;
            for (int y = 0; y < dim; y++) {
                M[x][y] = rand() % 100;
            }
        }

        for (int q = 0; q < count_threads; q++) {
            int threads = thread_set[q];

            double t_start = omp_get_wtime();
            multiply_matrix_vector(M, V, R, dim, threads);
            double t_end = omp_get_wtime();

            printf("Threads: %d, Time: %f seconds\n", threads, t_end - t_start);
        }

        for (int x = 0; x < dim; x++) {
            free(M[x]);
        }
        free(M);
        free(V);
        free(R);

        printf("\n");
    }

    return 0;
}
