#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_LIMIT 1024

void multiply_matrices(double **X, double **Y, double **Z, int dim, int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int a = 0; a < dim; a++) {
        for (int b = 0; b < dim; b++) {
            Z[a][b] = 0.0;
            for (int c = 0; c < dim; c++) {
                Z[a][b] += X[a][c] * Y[c][b];
            }
        }
    }
}

int main() {
    int dimensions[] = {512, 1024, 2048};
    int count_dim = sizeof(dimensions) / sizeof(dimensions[0]);
    int threads_set[] = {1, 2, 4, 8};
    int count_threads = sizeof(threads_set) / sizeof(threads_set[0]);

    for (int p = 0; p < count_dim; p++) {
        int dim = dimensions[p];
        printf("Size: %d x %d\n", dim, dim);

        double **X = (double **)malloc(dim * sizeof(double *));
        double **Y = (double **)malloc(dim * sizeof(double *));
        double **Z = (double **)malloc(dim * sizeof(double *));
        for (int a = 0; a < dim; a++) {
            X[a] = (double *)malloc(dim * sizeof(double));
            Y[a] = (double *)malloc(dim * sizeof(double));
            Z[a] = (double *)malloc(dim * sizeof(double));
        }

        for (int a = 0; a < dim; a++) {
            for (int b = 0; b < dim; b++) {
                X[a][b] = rand() % 100;
                Y[a][b] = rand() % 100;
            }
        }

        for (int q = 0; q < count_threads; q++) {
            int threads = threads_set[q];

            double t_start = omp_get_wtime();
            multiply_matrices(X, Y, Z, dim, threads);
            double t_end = omp_get_wtime();

            printf("Threads: %d, Time: %f seconds\n", threads, t_end - t_start);
        }

        for (int a = 0; a < dim; a++) {
            free(X[a]);
            free(Y[a]);
            free(Z[a]);
        }
        free(X);
        free(Y);
        free(Z);

        printf("\n");
    }

    return 0;
}
