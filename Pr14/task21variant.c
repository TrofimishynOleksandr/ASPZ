#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

// ==================== setitimer CLOCK ======================
void setitimer_handler(int sig) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char buf[64];
    strftime(buf, sizeof(buf), "\r%H:%M:%S", tm_info);
    write(STDOUT_FILENO, buf, strlen(buf));
    fsync(STDOUT_FILENO);
}

void run_setitimer_clock() {
    struct sigaction sa = {0};
    sa.sa_handler = setitimer_handler;
    sigaction(SIGALRM, &sa, NULL);

    struct itimerval timer = {
        .it_value.tv_sec = 1,
        .it_value.tv_usec = 0,
        .it_interval.tv_sec = 1,
        .it_interval.tv_usec = 0
    };

    setitimer(ITIMER_REAL, &timer, NULL);
    printf("CLI clock started (setitimer). Press Ctrl+C to stop.\n");

    while (1)
        pause();
}

// ==================== POSIX TIMERS =========================
void posix_timer_handler(int sig, siginfo_t *si, void *uc) {
    int thread_num = *(int *)si->si_value.sival_ptr;
    char msg[64];
    snprintf(msg, sizeof(msg), "Thread %d: tick\n", thread_num);
    write(STDOUT_FILENO, msg, strlen(msg));
}

void *posix_timer_thread(void *arg) {
    int thread_num = *(int *)arg;

    struct sigaction sa = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = posix_timer_handler;
    sigaction(SIGRTMIN + thread_num, &sa, NULL);

    timer_t timerid;
    struct sigevent sev = {0};
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN + thread_num;
    sev.sigev_value.sival_ptr = arg;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    struct itimerspec its = {
        .it_value.tv_sec = 1,
        .it_value.tv_nsec = 0,
        .it_interval.tv_sec = 2 + thread_num,
        .it_interval.tv_nsec = 0
    };

    timer_settime(timerid, 0, &its, NULL);

    while (1)
        pause();
}

void run_posix_timers() {
    const int num_threads = 2;
    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, posix_timer_thread, &thread_ids[i]);
    }

    printf("POSIX timers started in %d threads. Press Ctrl+C to stop.\n", num_threads);

    for (int i = 0; i < num_threads; ++i)
        pthread_join(threads[i], NULL);
}

int main() {
    int choice;
    printf("Select mode:\n");
    printf("1 - CLI clock (setitimer)\n");
    printf("2 - POSIX timers in threads\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        run_setitimer_clock();
    else if (choice == 2)
        run_posix_timers();
    else
        printf("Invalid choice\n");

    return 0;
}
