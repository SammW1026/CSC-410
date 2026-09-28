#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef SIZE
#define SIZE 100000000
#endif
#define NUM_THREADS 4

static long long *arr = NULL;
static long long partialSums[NUM_THREADS];

typedef struct {
    int thread_id;
    int start_index;
    int end_index;
} thread_data_t;

void *sumPart(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    long long local_sum = 0;

    for (int i = data->start_index; i < data->end_index; ++i) {
        local_sum += arr[i];
    }

    partialSums[data->thread_id] = local_sum;
    return NULL;
    
}

int main() {
    arr = (long long *)malloc(sizeof(long long) * SIZE);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for array.\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int chunk_size = SIZE / NUM_THREADS;
    int remainder = SIZE % NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].thread_id = i;
        thread_data[i].start_index = i * chunk_size;
        thread_data[i].end_index = (i + 1) * chunk_size;
        if (i == NUM_THREADS - 1) {
            thread_data[i].end_index += remainder;
        }

        partialSums[i] = 0;
        pthread_create(&threads[i], NULL, sumPart, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    long long totalSum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        totalSum += partialSums[i];
    }

    printf("Total Sum: %lld\n", totalSum);

    free(arr);
    return 0;
}
