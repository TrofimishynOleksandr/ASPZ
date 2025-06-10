#include "crash_logger.h"
#include <stddef.h>

int main() {
    install_crash_logger();
    int *ptr = NULL;
    *ptr = 42; //SIGSEGV
    return 0;
}
