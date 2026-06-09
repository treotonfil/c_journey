#include <stdio.h>
#include <stdlib.h>



int main() {
    int a = 2;
    int *pa = &a;
    int **ppa = &pa;

    *ppa = 6;

    printf("%d\n", a);
    printf("%p\n", pa);
    printf("%p\n", *ppa);
    return 0;
}

