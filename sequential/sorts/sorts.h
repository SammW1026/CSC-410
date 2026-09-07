#ifndef SORT_H
#define SORT_H

#ifndef SIZE
#define SIZE 30
#endif
#ifndef MAX_VAL
#define MAX_VAL 100000
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int arr[], int left, int right);
void bubbleSort(int arr[], int n);

void printArray(int arr[], int n);

#endif
