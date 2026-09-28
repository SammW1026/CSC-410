#ifndef MATRIX_T_H
#define MATRIX_T_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000
#define NUM_THREADS 4

int **A, **B, **C;

typedef struct {
    int thread_id;
    int start_row;
    int end_row;
} thread_data_t;

void *matrixMultiplyThread(void *arg);
void displayMatrix(int **matrix, int n);

#endif