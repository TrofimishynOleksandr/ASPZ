#include <stdio.h>
#include <stdlib.h>

void list_and_try(const char *path) {
    char cmd[512];

    printf("\nContents of %s:\n", path);
    snprintf(cmd, sizeof(cmd), "ls -l %s", path);
    system(cmd);

    printf("Trying to access files in %s...\n", path);
    snprintf(cmd, sizeof(cmd), "find %s -maxdepth 1 -type f | head -n 3 | while read f; do echo Trying $f; test -r $f && echo Readable; test -w $f && echo Writable; test -x $f && echo Executable; done", path);
    system(cmd);
}

int main() {
    list_and_try(getenv("HOME"));
    list_and_try("/usr/bin");
    list_and_try("/etc");

    return 0;
}
