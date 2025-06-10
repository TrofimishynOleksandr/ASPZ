#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    int status;

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child: I'm running!\n");
        exit(42);
    } else {
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent: Child exited with code %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child didn't exit normally\n");
        }
    }

    return 0;
}
