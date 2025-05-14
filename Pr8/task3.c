#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void generate_reverse(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = size - i;
}

void generate_equal(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = 1;
}

void generate_sorted(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = i;
}

void generate_random(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = rand() % size;
}

bool is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

void test_qsort(const char *label, void (*gen)(int *, int), int size) {
    int *arr = malloc(sizeof(int) * size);
    gen(arr, size);

    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    bool sorted = is_sorted(arr, size);
    
    printf("%-15s | Time: %-8.5f sec | %s\n", 
           label, elapsed, sorted ? "PASS" : "FAIL");

    free(arr);
}

int main() {
    int size = 10000000;
    test_qsort("Sorted", generate_sorted, size);
    test_qsort("Sorted", generate_sorted, size);
    test_qsort("Sorted", generate_sorted, size);

    test_qsort("Reverse sorted", generate_reverse, size);
    test_qsort("Reverse sorted", generate_reverse, size);
    test_qsort("Reverse sorted", generate_reverse, size);

    test_qsort("Equal", generate_equal, size);
    test_qsort("Equal", generate_equal, size);
    test_qsort("Equal", generate_equal, size);

    test_qsort("Random", generate_random, size);
    test_qsort("Random", generate_random, size);
    test_qsort("Random", generate_random, size);

    return 0;
}
