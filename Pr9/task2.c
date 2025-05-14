#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Trying to read /etc/master.passwd using sudo...\n");
    system("sudo cat /etc/master.passwd");
    return 0;
}
