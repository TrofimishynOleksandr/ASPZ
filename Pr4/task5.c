#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t big_size = SIZE_MAX / 2;
    void *ptr = malloc(128);
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    void *newptr = realloc(ptr, big_size);
    if (!newptr) {
        perror("realloc failed");
        free(ptr);
    } else {
        printf("Reallocated to %zu bytes\n", big_size);
        free(newptr);
    }

    return 0;
}
