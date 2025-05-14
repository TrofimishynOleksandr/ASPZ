#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Running whoami:\n");
    system("whoami");

    printf("\nRunning id:\n");
    system("id");

    return 0;
}
