#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#define MAX_PATH 4096
#define MAX_FILES_IN_DIR 100

int max_depth = 0;
int symlink_count = 0;
int cluttered_dirs = 0;
int suspected_cycles = 0;

void analyze_directory(const char *path, int depth) {
    if (depth > max_depth)
        max_depth = depth;

    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    char fullpath[MAX_PATH];
    int file_count = 0;

    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        lstat(fullpath, &st);

        if (S_ISLNK(st.st_mode)) {
            symlink_count++;
            if (strstr(entry->d_name, ".."))
                suspected_cycles++;
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            analyze_directory(fullpath, depth + 1);
        }

        file_count++;
    }

    if (file_count > MAX_FILES_IN_DIR)
        cluttered_dirs++;

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *start_path = argc > 1 ? argv[1] : ".";

    analyze_directory(start_path, 1);

    printf("=== Directory Complexity Analysis ===\n");
    printf("Analyzed path: %s\n", start_path);
    printf("Max depth: %d\n", max_depth);
    printf("Number of symbolic links: %d\n", symlink_count);
    printf("Cluttered directories (> %d files): %d\n", MAX_FILES_IN_DIR, cluttered_dirs);
    printf("Suspected cycles (symbolic '..'): %d\n", suspected_cycles);

    int complexity_score = max_depth + cluttered_dirs * 2 + symlink_count + suspected_cycles * 3;
    printf("Complexity score: %d / 100\n", complexity_score > 100 ? 100 : complexity_score);

    return 0;
}
