#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main() {
    printf("sizeof(size_t) = %zu bytes\n", sizeof(size_t));
    printf("Maximum size_t = %zu\n", SIZE_MAX);

    size_t max_size = SIZE_MAX;
    void *ptr = malloc(max_size);
    if (ptr) {
        printf("malloc(SIZE_MAX) succeeded\n");
        free(ptr);
    } else {
        perror("malloc failed");
    }
    return 0;
}
