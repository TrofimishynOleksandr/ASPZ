#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[1])) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
