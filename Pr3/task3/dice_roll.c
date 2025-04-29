#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void handle_sigxfsz(int sig) {
    fprintf(stderr, "File size limit reached. Program terminated.\n");
    exit(1);
}

int main() {
    signal(SIGXFSZ, handle_sigxfsz);

    FILE *file = fopen("dice_rolls.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < 1000000; i++) {
        int roll = (rand() % 6) + 1;
        if (fprintf(file, "%d\n", roll) < 0) {
            perror("Error writing to file");
            break;
        }
    }

    fclose(file);
    return 0;
}