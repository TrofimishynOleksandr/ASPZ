#define _GNU_SOURCE
#include "crash_logger.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <unistd.h>
#include <string.h>
#include <ucontext.h>
#include <fcntl.h>

void crash_handler(int sig, siginfo_t *info, void *ucontext) {
    int fd = open("crash.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) _exit(1);

    dprintf(fd, "\n=== Crash Report ===\n");
    dprintf(fd, "Signal: %d (%s)\n", sig, strsignal(sig));
    dprintf(fd, "Fault address: %p\n", info->si_addr);
    dprintf(fd, "Sender PID: %d\n", info->si_pid);

    void *trace[20];
    int trace_size = backtrace(trace, 20);
    backtrace_symbols_fd(trace, trace_size, fd);

    dprintf(fd, "=== End of Report ===\n\n");
    close(fd);
    _exit(1);
}

void install_crash_logger() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = crash_handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
}
