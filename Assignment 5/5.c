#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MATRIX_SIZE 1024 // Define the size of the matrices

void initializeMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 100; // Initialize with random values
        }
    }
}

void serialMatrixMultiplication(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void parallelMatrixMultiplicationStatic(double** A, double** B, double** C, int size) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void parallelMatrixMultiplicationDynamic(double** A, double** B, double** C, int size) {
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double** createMatrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; ++i) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }
    return matrix;
}

void deleteMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int sizes[] = {512, 1024, 2048};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int index = 0; index < num_sizes; ++index) {
        int size = sizes[index];

        // Allocate and initialize matrices
        double** A = createMatrix(size);
        double** B = createMatrix(size);
        double** C = createMatrix(size);
        double** C_serial = createMatrix(size);

        initializeMatrix(A, size);
        initializeMatrix(B, size);

        // Serial multiplication
        double start_time = omp_get_wtime();
        serialMatrixMultiplication(A, B, C_serial, size);
        double end_time = omp_get_wtime();
        double serial_time = end_time - start_time;

        printf("Matrix size: %d x %d\n", size, size);
        printf("Serial execution time: %f seconds\n", serial_time);

        // Parallel static scheduling multiplication
        start_time = omp_get_wtime();
        parallelMatrixMultiplicationStatic(A, B, C, size);
        end_time = omp_get_wtime();
        double static_time = end_time - start_time;

        printf("Static scheduling execution time: %f seconds\n", static_time);

        // Parallel dynamic scheduling multiplication
        start_time = omp_get_wtime();
        parallelMatrixMultiplicationDynamic(A, B, C, size);
        end_time = omp_get_wtime();
        double dynamic_time = end_time - start_time;

        printf("Dynamic scheduling execution time: %f seconds\n", dynamic_time);

        // Cleanup
        deleteMatrix(A, size);
        deleteMatrix(B, size);
        deleteMatrix(C, size);
        deleteMatrix(C_serial, size);

        printf("\n");
    }

    return 0;
}
