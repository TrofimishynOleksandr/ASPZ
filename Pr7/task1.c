#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("who | more", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    pclose(fp);
    return 0;
}
