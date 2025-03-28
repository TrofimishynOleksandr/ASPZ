#include <stdio.h>

void func() {
    int uninit_arr[1000];
    int init_arr[1000] = {0};
}

int main() {
    printf("Hello, World!\n");
    func();
    return 0;
}