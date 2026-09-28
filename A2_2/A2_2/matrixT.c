#include "matrixT.h"

void *matrixMultiplyThread(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    for (int i = data->start_row; i < data->end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return NULL;
}

void displayMatrix(int **matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    A = (int **)malloc(N * sizeof(int *));
    B = (int **)malloc(N * sizeof(int *));
    C = (int **)malloc(N * sizeof(int *));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    for (int i = 0; i < N; ++i) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
        if (A[i] == NULL || B[i] == NULL || C[i] == NULL) {
            printf("Matrix row allocation failed!\n");
            return -1;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int rows_per_thread = N / NUM_THREADS;
    int remainder = N % NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].thread_id = i;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i + 1) * rows_per_thread;
        if (i == NUM_THREADS - 1) {
            thread_data[i].end_row += remainder;
        }
        pthread_create(&threads[i], NULL, matrixMultiplyThread, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix multiplication complete!\n");
    printf("Sample result C[0][0] = %d, C[0][1] = %d\n", C[0][0], C[0][1]);

    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}