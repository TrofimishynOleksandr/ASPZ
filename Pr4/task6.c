#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr1 = realloc(NULL, 128);
    printf("realloc(NULL, 128) = %p\n", ptr1);
    free(ptr1);

    void *ptr2 = malloc(128);
    void *ptr3 = realloc(ptr2, 0);
    printf("realloc(ptr, 0) = %p\n", ptr3);

    return 0;
}
