#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_NUM_49 7
#define MAX_NUM_36 6

void handle_sigxcpu(int sig) {
    printf("\nCPU time limit exceeded. Program terminated.\n");
    exit(EXIT_SUCCESS);
}

void generate_numbers(int *arr, int size, int max_value) {
    for (int i = 0; i < size; i++) {
        int num;
        int unique;
        do {
            unique = 1;
            num = rand() % max_value + 1;
            for (int j = 0; j < i; j++) {
                if (arr[j] == num) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
        arr[i] = num;
    }
}

int main() {
    signal(SIGXCPU, handle_sigxcpu);

    struct rlimit cpu_limit;
    cpu_limit.rlim_cur = 1;
    cpu_limit.rlim_max = 2;
    setrlimit(RLIMIT_CPU, &cpu_limit);

    srand(time(NULL));

    int numbers_49[MAX_NUM_49];
    int numbers_36[MAX_NUM_36];

    while (1) {
        generate_numbers(numbers_49, MAX_NUM_49, 49);
        generate_numbers(numbers_36, MAX_NUM_36, 36);

        printf("7 of 49: ");
        for (int i = 0; i < MAX_NUM_49; i++) {
            printf("%d ", numbers_49[i]);
        }
        printf("\n");

        printf("6 of 36: ");
        for (int i = 0; i < MAX_NUM_36; i++) {
            printf("%d ", numbers_36[i]);
        }
        printf("\n");
    }

    return 0;
}
