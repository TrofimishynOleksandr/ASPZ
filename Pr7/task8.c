#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char answer;

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) {
            printf("Delete file %s? (y/n): ", entry->d_name);
            answer = getchar();
            getchar();
            if (answer == 'y') {
                remove(entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
