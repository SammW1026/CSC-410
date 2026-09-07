#include "sorts.h"

// Merge Sort 
static void merge(int arr[], int left, int mid, int right) 
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int *leftPart = (int *)malloc(leftSize * sizeof(int));
    int *rightPart = (int *)malloc(rightSize * sizeof(int));

    if (leftPart == NULL || rightPart == NULL) {
        free(leftPart);
        free(rightPart);
        return;
    }

    for (int i = 0; i < leftSize; i++) {
        leftPart[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightPart[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < leftSize && j < rightSize) {
        if (leftPart[i] <= rightPart[j]) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = leftPart[i++];
    }
    while (j < rightSize) {
        arr[k++] = rightPart[j++];
    }

    free(leftPart);
    free(rightPart);
}

void mergeSort(int arr[], int left, int right) 
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void printArray(int arr[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}