#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void memory_leak() {
    char *leak = malloc(50);
    strcpy(leak, "Цей рядок викликає витік пам’яті!");
    printf("%s\n", leak);
}

void use_after_free() {
    char *data = malloc(20);
    strcpy(data, "Hello, world!");
    free(data);
    printf("%s\n", data);
}

int main() {
    memory_leak();
    use_after_free();
    return 0;
}
