#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *tempfile = "/tmp/tempfile.txt";
    FILE *f = fopen(tempfile, "w");
    if (!f) {
        perror("fopen (create)");
        return 1;
    }
    fprintf(f, "Temporary file content\n");
    fclose(f);

    printf("Created file: %s\n", tempfile);

    printf("Changing owner and permissions with sudo...\n");
    char command[512];
    snprintf(command, sizeof(command),
             "sudo chown root:wheel %s && sudo chmod 644 %s",
             tempfile, tempfile);
    system(command);

    printf("Trying to read file as current user...\n");
    f = fopen(tempfile, "r");
    if (!f) {
        perror("fopen (read)");
    } else {
        char buf[256];
        size_t n = fread(buf, 1, sizeof(buf) - 1, f);
        buf[n] = '\0';
        printf("File content: %s\n", buf);
        fclose(f);
    }

    printf("Trying to append to file as current user...\n");
    f = fopen(tempfile, "a");
    if (!f) {
        perror("fopen (append)");
    } else {
        fprintf(f, "Appended line\n");
        fclose(f);
        printf("Append successful\n");
    }

    return 0;
}
