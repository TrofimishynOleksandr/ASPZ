#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("datafile.bin", O_RDWR | O_CREAT, 0644);
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(fd, data, sizeof(data));

    lseek(fd, 3, SEEK_SET);
    unsigned char buffer[4];
    read(fd, buffer, 4);

    printf("Buffer contents: ");
    for (int i = 0; i < 4; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    close(fd);
    return 0;
}
