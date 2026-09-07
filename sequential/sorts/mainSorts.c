#include "sorts.h"

int main() 
{
    srand(time(NULL));

    // Dynamically allocate arrays
    int *arr1 = (int*)malloc(SIZE * sizeof(int));
    int *arr2 = (int*)malloc(SIZE * sizeof(int));

    if (!arr1 || !arr2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Populate arrays with random values
    for (int i = 0; i < SIZE; i++) {
        int val = rand() % MAX_VAL;
        arr1[i] = val;
        arr2[i] = val;
    }

    printf("Original array:\n");
    printArray(arr1, SIZE);

        clock_t mergeStart = clock();
        mergeSort(arr1, 0, SIZE - 1);
        clock_t mergeEnd = clock();
    printf("Sorted with Merge Sort:\n");
    printArray(arr1, SIZE);
        printf("Merge sort time: %.6f seconds\n",
            (double)(mergeEnd - mergeStart) / CLOCKS_PER_SEC);

        clock_t bubbleStart = clock();  
    bubbleSort(arr2, SIZE);
        clock_t bubbleEnd = clock();
    printf("Sorted with Bubble Sort:\n");
    printArray(arr2, SIZE);
        printf("Bubble sort time: %.6f seconds\n",
            (double)(bubbleEnd - bubbleStart) / CLOCKS_PER_SEC);

    free(arr1);
    free(arr2);

    return 0;
}
