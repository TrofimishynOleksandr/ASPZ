#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/resource.h>
#include <signal.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void handle_sigxfsz(int sig) {
    fprintf(stderr, "Reached file size limit.\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    signal(SIGXFSZ, handle_sigxfsz);

    struct rlimit limit;
    limit.rlim_cur = 1024;
    limit.rlim_max = 2048;
    setrlimit(RLIMIT_FSIZE, &limit);

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd < 0) {
        fprintf(stderr, "Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        fprintf(stderr, "Cannot open file %s for writing\n", argv[2]);
        close(input_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(output_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            perror("Error writing to file");
            break;
        }
    }

    close(input_fd);
    close(output_fd);
    return 0;
}
