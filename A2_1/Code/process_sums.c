// convert sequential sums to parallel

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 4

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "N must be positive\n");
        return 1;
    }

    int *arr = malloc((size_t)N * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    int chunk_size = (N + NUM_PROCESSES - 1) / NUM_PROCESSES;
    int pipefds[NUM_PROCESSES][2];
    pid_t pids[NUM_PROCESSES];
    long long total = 0;

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (pipe(pipefds[i]) == -1) {
            perror("pipe");
            free(arr);
            return 1;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            for (int j = 0; j <= i; j++) {
                close(pipefds[j][0]);
                close(pipefds[j][1]);
            }
            free(arr);
            return 1;
        }

        if (pid == 0) {
            close(pipefds[i][0]);

            int start = i * chunk_size;
            int end = start + chunk_size;
            if (end > N) {
                end = N;
            }

            long long partial_sum = 0;
            for (int j = start; j < end; j++) {
                partial_sum += arr[j];
            }

            if (write(pipefds[i][1], &partial_sum, sizeof(partial_sum)) == -1) {
                perror("write");
            }

            close(pipefds[i][1]);
            free(arr);
            _exit(0);
        }

        pids[i] = pid;
        close(pipefds[i][1]);
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        long long partial_sum = 0;
        ssize_t bytes_read = read(pipefds[i][0], &partial_sum, sizeof(partial_sum));
        if (bytes_read == -1) {
            perror("read");
        }
        if (bytes_read > 0) {
            total += partial_sum;
        }
        close(pipefds[i][0]);
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }

    printf("Total sum = %lld\n", total);
    free(arr);

    return 0;
}
