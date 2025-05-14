#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define SLEEP_INTERVAL 1

void print_new_content(int fd, off_t *offset) {
    char buffer[BUFFER_SIZE];
    lseek(fd, *offset, SEEK_SET);
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
        *offset += bytes_read;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_to_follow>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat file_stat;
    off_t current_offset;

    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    current_offset = file_stat.st_size;

    while (1) {
        if (fstat(fd, &file_stat) == -1) {
            perror("fstat");
            break;
        }

        if (file_stat.st_size > current_offset) {
            print_new_content(fd, &current_offset);
        }

        sleep(SLEEP_INTERVAL);
    }

    close(fd);
    return 0;
}
