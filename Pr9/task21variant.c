#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "/tmp/testfile.txt";

    int fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, "Hello, world!\n", 14);
    lseek(fd, 0, SEEK_SET);

    printf("File created and written: %s\n", filename);

    if (unlink(filename) != 0) {
        perror("unlink");
        return 1;
    }

    printf("File unlinked (deleted): %s\n", filename);

    char buffer[128];
    ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes < 0) {
        perror("read");
    } else {
        buffer[bytes] = '\0';
        printf("Read from open file descriptor after unlink: %s", buffer);
    }
c
    printf("Sleeping 10 seconds — check /proc/`pid`/fd...\n");
    sleep(10);

    close(fd);
    printf("File descriptor closed — now file is truly gone.\n");

    return 0;
}
