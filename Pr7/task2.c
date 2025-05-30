#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";
    if (S_ISDIR(mode)) perms[0] = 'd';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
    printf("%s ", perms);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &file_stat);
        print_permissions(file_stat.st_mode);
        printf("%ld ", file_stat.st_nlink);
        printf("%s %s ", getpwuid(file_stat.st_uid)->pw_name, getgrgid(file_stat.st_gid)->gr_name);
        printf("%5ld ", file_stat.st_size);
        printf("%.12s ", 4 + ctime(&file_stat.st_mtime));
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
