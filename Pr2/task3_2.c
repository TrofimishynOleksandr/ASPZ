#include <stdio.h>
#include <stdlib.h>

int global_var = 42;
static int static_var = 100;

void dummy_function() {}

void increase_stack() {
    char large_array[1024 * 1024];
    printf("After allocation, stack top is near %p\n", &large_array[0]);
}

int main() {
    int local_var;
    
    int *heap_var = (int *)malloc(sizeof(int));
    if (!heap_var) {
        perror("malloc failed");
        return 1;
    }
    *heap_var = 2024;

    printf("Text segment (function): %p\n", (void *)dummy_function);
    printf("Data segment (global var): %p\n", (void *)&global_var);
    printf("Data segment (static var): %p\n", (void *)&static_var);
    printf("Heap (malloc): %p\n", (void *)heap_var);
    printf("Stack (local var): %p\n", (void *)&local_var);
    
    increase_stack();

    free(heap_var);
    return 0;
}
