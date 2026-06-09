#include <stdio.h>
#include <stdlib.h>

struct Node *create_node(int value);
void print_list(struct Node *list);
void free_list(struct Node *list);
void append(struct Node **head, int value);
void prepend(struct Node **head, int value);
struct Node *find(struct Node *head, int value);
void delete_node(struct Node **head, int value);


struct Node {
    int value;
    struct Node *next;
};

int main() {
    struct Node *n1 = NULL;

    append(&n1, 4);
    append(&n1, 0);
    append(&n1, 3);
    append(&n1, 1);
    append(&n1, 9);
    prepend(&n1, 7);


    struct Node *a = find(n1, 3);
    
    print_list(n1);
    printf("%d", a->value);
    free_list(n1);
    return 0;
}

struct Node *create_node(int val){
    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL) {
        printf("Failed");
        return NULL;
    }

    node->value = val;
    node->next = NULL;

    return node;
}

void print_list(struct Node *list) {
    while(list != NULL) {
        printf("%d\n", list->value);
        list = list->next;
    }
}

void free_list(struct Node *list) {
    while (list != NULL) {
        struct Node *temp = list->next;
        free(list);
        list = temp;
    }
}

void append(struct Node **head, int value) {
    if (*head == NULL){
        *head = create_node(value);
    } else {
        struct Node *current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = create_node(value);
    }
}

void prepend(struct Node **head, int value) {
    struct Node *next = *head;
    *head = create_node(value);
    (*head)->next = next;
}

struct Node *find(struct Node *head, int value) {
    while (head != NULL){
        if (head->value == value) return head;
        head = head->next;
    }
    return NULL;
}

void delete_node(struct Node **head, int value) {
    if (*head == NULL || find(*head, value) == NULL) {
    } else if ((*head)->value == value){
        struct Node *to_delete = *head;
        *head = (*head)->next;
        free(to_delete);
    } else {
        struct Node *current = *head;
        while (current->next != NULL && current->next->value != value) {
            current = current->next;
        }
        struct Node *to_delete = current->next;
        current->next = current->next->next; 
        free(to_delete);
    }
}