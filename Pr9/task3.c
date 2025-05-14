#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    char *filename = "/tmp/userfile.txt";
    char *copy = "/home/admin/copiedfile.txt";

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "This is a test.\n");
    fclose(f);

    printf("File created by user: %s\n", filename);
    printf("Now copy it as root...\n");

    system("sudo cp /tmp/userfile.txt /home/admin/copiedfile.txt");
    system("sudo chown admin:admin /home/admin/copiedfile.txt");
    printf("Try modifying the file as user...\n");

    f = fopen(copy, "a");
    if (f) {
        fprintf(f, "Appended line.\n");
        fclose(f);
        printf("File successfully modified.\n");
    } else {
        perror("fopen");
    }

    printf("Now deleting the file...\n");
    if (remove(copy) == 0) {
        printf("File deleted.\n");
    } else {
        perror("remove");
    }

    return 0;
}
