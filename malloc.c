#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Header {
    size_t size;
    int free;
    struct Header *next;
} Header;

Header *free_list = NULL;

void my_free(void *ptr);
void *my_malloc(size_t size);

int main() {
    int *a = (int *)my_malloc(sizeof(int));
    *a = 42;
    printf("%d\n", *a);
    my_free(a);

    int *b = (int *)my_malloc(sizeof(int));
    printf("%d\n", *b);
    my_free(b);

    return 0;
}

void my_free(void *ptr) {
    Header *h = (Header *)ptr - 1;
    h->free = 1;
}

void *my_malloc(size_t size) {
    Header *current = free_list;

    if (current != NULL) {
        while(current != NULL) {
            if (current->free == 1 && current->size >= size) {
                current->free = 0;
                return (void *)(current + 1);
            }
            current = current->next;
        }
    }

    current = free_list;
    void *mem = sbrk(sizeof(Header) + size);
    Header *new = (Header *)mem;
    new->size = size;
    new->free = 0;
    new->next = NULL;

    if (free_list == NULL) {
        free_list = new;
    } else {
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
    
    return (void *)(new + 1);
}