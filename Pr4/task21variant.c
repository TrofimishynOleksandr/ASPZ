#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#define ALLOC_SIZE (1024 * 1024) // 1 MB

int main() {
    struct rlimit rl;
    rl.rlim_cur = 20 * 1024 * 1024; // 20 MB
    rl.rlim_max = 20 * 1024 * 1024;

    if (setrlimit(RLIMIT_AS, &rl) != 0) {
        perror("setrlimit");
        return 1;
    }

    size_t total = 0;
    while (1) {
        void* p = malloc(ALLOC_SIZE);
        if (!p) {
            perror("malloc");
            break;
        }
        total += ALLOC_SIZE;
        printf("Allocated %zu MB\n", total / (1024 * 1024));
    }

    printf("Total allocated before failure: %zu MB\n", total / (1024 * 1024));
    return 0;
}
