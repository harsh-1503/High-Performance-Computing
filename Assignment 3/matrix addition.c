#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void performMatrixAddition(int dimension, int thread_count)
{
    int row, col;
    double start_time, end_time;

    int **matrixX = (int **)malloc(dimension * sizeof(int *));
    int **matrixY = (int **)malloc(dimension * sizeof(int *));
    int **matrixZ = (int **)malloc(dimension * sizeof(int *));

    for (row = 0; row < dimension; row++)
    {
        matrixX[row] = (int *)malloc(dimension * sizeof(int));
        matrixY[row] = (int *)malloc(dimension * sizeof(int));
        matrixZ[row] = (int *)malloc(dimension * sizeof(int));
    }

    for (row = 0; row < dimension; row++)
    {
        for (col = 0; col < dimension; col++)
        {
            matrixX[row][col] = row + col;
            matrixY[row][col] = row - col;
        }
    }

    omp_set_num_threads(thread_count);
    start_time = omp_get_wtime();

#pragma omp parallel for collapse(2)
    for (row = 0; row < dimension; row++)
    {
        for (col = 0; col < dimension; col++)
        {
            matrixZ[row][col] = matrixX[row][col] + matrixY[row][col];
        }
    }

    end_time = omp_get_wtime();
    printf("Dimension: %d, Threads: %d, Execution Time: %f seconds\n", dimension, thread_count, end_time - start_time);
}

int main()
{
    int dimensions[] = {250, 500, 750, 1000, 2000};
    int thread_options[] = {1, 2, 4, 8, 16};

    for (int dimension_index = 0; dimension_index < 5; dimension_index++)
    {
        for (int thread_index = 0; thread_index < 5; thread_index++)
        {
            performMatrixAddition(dimensions[dimension_index], thread_options[thread_index]);
        }
    }

    return 0;
}
