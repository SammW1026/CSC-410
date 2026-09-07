#include <stdio.h>
#include <time.h>

#ifndef SIZE
#define SIZE 10000
#endif

int sumArray(int arr[], int size) 
{
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

int main() 
{
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1; 
    }

    clock_t start = clock();
    int totalSum = sumArray(arr, SIZE);
    clock_t end = clock();
    printf("Total Sum: %d\n", totalSum);
    printf("Array sum time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
