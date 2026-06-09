#include <stdio.h>
#include <stdlib.h>

struct Stack *create_stack(int value);
void push(struct Stack **top, int value);
int pop(struct Stack **top);
void peek(struct Stack *top);
void print_stack(struct Stack *top);
void free_stack(struct Stack *top);

struct Stack {
    int value;
    struct Stack *next;
};

int main() {
    struct Stack *my_stack = NULL;

    push(&my_stack, 1);
    push(&my_stack, 3);
    push(&my_stack, 2);
    peek(my_stack);

    printf("%d\n", pop(&my_stack));
    print_stack(my_stack);
    
    free_stack(my_stack);
    return 0;
}

struct Stack *create_stack(int value) {
    struct Stack *new = malloc(sizeof(struct Stack));
    if (new == NULL){
        return NULL;
    }

    new->value = value;
    new->next = NULL;
    return new;
}

void push(struct Stack **top, int value) {
    struct Stack *current = *top;
    *top = create_stack(value);
    (*top)->next = current;
}

int pop(struct Stack **top) {
    if (*top == NULL) exit(1);

    int the_top = (*top)->value;
    struct Stack *temp = *top;
    *top = (*top)->next;
    free(temp);
    return the_top;
}

void peek(struct Stack *top) {
    if (top != NULL) {
        printf("%d\n", top->value);
    }
}

void free_stack(struct Stack *top) {
    while (top != NULL) {
        struct Stack *temp = top->next;
        free(top);
        top = temp;
    }
}

void print_stack(struct Stack *top) {
    while (top != NULL) {
        printf("%d ", top->value);
        top = top->next;
    }
    printf("\n");
}
