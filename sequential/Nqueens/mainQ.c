#include "nqueens.h"
#include <time.h> 

#ifndef QUEENS_N
#define QUEENS_N 8
#endif

int main() 
{
    int n = QUEENS_N;
    int* board = (int*)malloc(n * sizeof(int));
    if (board == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        board[i] = -1;
    }

        clock_t start = clock();
        solveNQueensUtil(board, 0, n);
        clock_t end = clock();
        printf("N-Queens time: %.6f seconds\n",
            (double)(end - start) / CLOCKS_PER_SEC);

    free(board);
    return 0;
}
