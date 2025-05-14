#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float rand_float(float n) {
    return ((float)rand() / RAND_MAX) * n;
}

int main() {
    int i;
    float n;

    srand(time(NULL));

    printf("From 0.0 to 1.0:\n");
    for (i = 0; i < 5; ++i) {
        printf("%.6f\n", rand_float(1));
    }

    printf("\nEnter value n for numbers generaation in [0.0; n]: ");
    if (scanf("%f", &n) != 1 || n <= 0) {
        printf("Invalid n value.\n");
        return 1;
    }

    printf("From 0.0 to %2f:\n", n);
    for (i = 0; i < 5; ++i) {
        printf("%.6f\n", rand_float(n));
    }

    return 0;
}
