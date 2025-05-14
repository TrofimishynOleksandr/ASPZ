#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20
#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAX_LINE];
    int line_count = 0;

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (!fp) continue;

        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
            if (++line_count % LINES_PER_PAGE == 0) {
                printf("--Press Enter to continue--");
                getchar();
            }
        }

        fclose(fp);
    }

    return 0;
}
