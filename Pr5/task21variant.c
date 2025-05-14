#include <stdio.h>
#include <string.h>

int main() {
    char buffer[5];
    int secret = 12345;

    printf("Before: secret = %d\n", secret);

    strcpy(buffer, "ABCDEFG");

    printf("After: secret = %d\n", secret);

    return 0;
}
