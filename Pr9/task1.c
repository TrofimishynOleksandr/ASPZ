#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

int main() {
    struct passwd *pw;
    uid_t my_uid = getuid();

    printf("Current UID: %d\n", my_uid);
    printf("Regular users (UID > 1000), except you:\n");

    setpwent();
    while ((pw = getpwent()) != NULL) {
        if (pw->pw_uid > 1000 && pw->pw_uid != my_uid) {
            printf("User: %s, UID: %d\n", pw->pw_name, pw->pw_uid);
        }
    }
    endpwent();
    return 0;
}
