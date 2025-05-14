#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr = NULL;
    int count = 0;
    int n = 8;
    while (count++ < 3) {
        if (!ptr)
            ptr = malloc(n);
        
        strcpy((char*)ptr, "Hello");
        printf("ptr: %s\n", (char*)ptr);

        free(ptr);
    }
    return 0;
}
