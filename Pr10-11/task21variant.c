#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    } else if (pid1 == 0) {
        printf("Child 1: Hello from the first child process!\n");
        exit(0);
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    } else if (pid2 == 0) {
        printf("Child 2: Hello from the second child process!\n");
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Parent: Both child processes have finished.\n");

    return 0;
}
