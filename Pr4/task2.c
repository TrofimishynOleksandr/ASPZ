#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb;

    printf("xa = %d, xb = %d, num = %d (overflowed)\n", xa, xb, num);

    void *ptr = malloc(num);
    if (ptr) {
        printf("malloc(%zu) succeeded\n", (size_t) num);
        free(ptr);
    } else {
        printf("malloc failed: cannot allocate %zu bytes\n", (size_t) num);
    }
    return 0;
}
