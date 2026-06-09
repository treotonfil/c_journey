#include <stdio.h>

void swap(int *a, int *b);

int main() {
    int a = 5;
    int b = 9;
    swap(&a, &b);
    printf("Hello a: %d, b: %d", a, b);
    return 0;
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
