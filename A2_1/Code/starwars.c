#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Starting shield power level
int shield_power = 50;

int main(void) {
    pid_t pid;
    const char *characters[] = {"Luke", "Han", "Chewbacca", "Leia"};
    int adjustments[] = {25, 20, 30, 15};

    printf("Millennium Falcon: Initial shield power level: %d%%\n\n", shield_power);

    for (int i = 0; i < 4; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            printf("%s: Adjusting shield power...\n", characters[i]);
            shield_power += (shield_power * adjustments[i]) / 100;
            printf("%s: Shield power level now at %d%%\n", characters[i], shield_power);
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    printf("\nFinal shield power level on the Millennium Falcon: %d%%\n", shield_power);
    printf("\nMay the forks be with you!\n");
    return 0;
}
