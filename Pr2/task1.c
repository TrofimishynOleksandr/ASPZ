#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    time_t max_time;

    if (sizeof(time_t) == 4) {
        max_time = (time_t) INT_MAX;
    } else if (sizeof(time_t) == 8) {
        max_time = (time_t) LLONG_MAX;
    }

    printf("Максимальне значення time_t: %lld\n", (long long)max_time);
    printf("Дата і час: %s\n", ctime(&max_time));
    
    return 0;
}