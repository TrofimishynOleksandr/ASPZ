#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (!dir) return;

    chdir(path);
    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        stat(entry->d_name, &st);
        if (S_ISDIR(st.st_mode)) {
            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
                printf("[DIR] %s/%s\n", path, entry->d_name);
                list_files(entry->d_name);
            }
        } else {
            printf("%s/%s\n", path, entry->d_name);
        }
    }

    chdir("..");
    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
