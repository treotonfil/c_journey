#include <stdio.h>
#include <stdlib.h>

int* make_array(int y);


int main() {
    int *my_arr = make_array(5);

    for (int i = 0; i < 5; i++) {
        printf("%d\n", my_arr[i]);
    }

    free(my_arr);
    my_arr = NULL;

    return 0;
}

int* make_array(int y) {
    int *my_arr = malloc(y * sizeof(int));
    for (int i = 0; i < y; i++) {
        my_arr[i] = i + 1;
    }
    
    return my_arr;
}