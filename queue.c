#include <stdio.h>
#include <stdlib.h>

struct Queue *create_queue(int value);
void enqueue(struct Queue **head, struct Queue **tail, int value);
int dequeue(struct Queue **head, struct Queue **tail);
void print_queue(struct Queue *head);
void free_q(struct Queue *head);


struct Queue {
    int value;
    struct Queue *next;
};

int main() {
    struct Queue *h = NULL;
    struct Queue *t = NULL;

    enqueue(&h, &t, 6);

    printf("%d\n", dequeue(&h, &t));

    free_q(h);

    return 0;
}

struct Queue *create_node(int value) {
    struct Queue *q = malloc(sizeof(struct Queue));

    if (q == NULL) {
        return NULL;
    }

    q->value = value;
    q->next = NULL;

    return q;
}

void enqueue(struct Queue **head, struct Queue **tail, int value) {
    if (*head == NULL && *tail == NULL) {
        *head = create_node(value);
        *tail = *head;
    } else {
        struct Queue *new_node = create_node(value);
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int dequeue(struct Queue **head, struct Queue **tail) {
    if (*head == NULL && *tail == NULL) return EXIT_SUCCESS;

    if (*head == *tail) {
        int hej = (*head)->value;
        free(*head);
        *head = NULL;
        *tail = NULL;
        return hej;
    } 
    struct Queue *temp = (*head)->next;
    int hej = (*head)->value;
    free(*head);
    *head = temp;
    if (*head == NULL) {
        *tail = NULL;
    }
    return hej;
}

void print_queue(struct Queue *head) {
    while (head != NULL) {
        printf("%d\n", head->value);
        head = head->next;
    }
}

void free_q(struct Queue *head) {
    while(head != NULL) {
        struct Queue *temp = head->next;
        free(head);
        head = temp;
    }
}

