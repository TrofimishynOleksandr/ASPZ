#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int is_directory(const char *name) {
    struct stat st;
    stat(name, &st);
    return S_ISDIR(st.st_mode);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char *dirs[100];
    int count = 0;

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            dirs[count++] = strdup(entry->d_name);
        }
    }

    qsort(dirs, count, sizeof(char *), (int(*)(const void*, const void*))strcmp);

    for (int i = 0; i < count; ++i) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    closedir(dir);
    return 0;
}
