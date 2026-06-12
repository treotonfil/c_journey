#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


#define TABLE_SIZE 256

unsigned int hash(char *word);
struct HT *create_table();
void insert(struct HT *ht, char *word);
void print_count(struct HT *ht, char *word);
void free_table(struct HT *ht);
void print_table(struct HT *ht);
void trim_special(char *word);
void count_words(struct HT *ht, char *filename);

struct Entry {
    char *word;
    int count;
    struct Entry *next;
};

struct HT {
    struct Entry *arr[TABLE_SIZE];
    int size;
};

int main() {
    struct HT *ht = create_table();
    count_words(ht, "words.txt");
    print_table(ht);
    free_table(ht);
    return 0;
}

unsigned int hash(char *word) {
    unsigned int h = 5831;
    while (*word) {
        h = h * 33 + *word;
        word++;
    }
    return h % TABLE_SIZE;
}

struct HT *create_table() {
    struct HT *ht = malloc(sizeof(struct HT));

    if (ht == NULL) {
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->arr[i] = NULL;
    }
    ht->size = 0;

    return ht;
}

void insert(struct HT *ht, char *word) {
    unsigned int index = hash(word);
    struct Entry *e = ht->arr[index];

    while(e != NULL) {
        if(strcmp(e->word, word) == 0) {
            e->count++;
            break;
        }
        e = e->next;
    }

    if (e == NULL) {
        struct Entry *new = malloc(sizeof(struct Entry));
        struct Entry *temp = ht->arr[index];
        new->word = strdup(word);
        new->count = 1;
        new->next = temp;
        ht->arr[index] = new;
        ht->size++;
    }
}

void free_table(struct HT *ht) {
    for (int i =0; i < TABLE_SIZE; i++) {
        struct Entry *e = ht->arr[i];
        while (e != NULL) {
            struct Entry *temp = e->next;
            free(e->word);
            free(e);
            e = temp;
        }
    }
    free(ht);
}

void print_table(struct HT *ht) {
    for (int i=0; i < TABLE_SIZE; i++) {
        struct Entry *e = ht->arr[i];
        while(e != NULL) {
            printf("%s: %d\n", e->word, e->count);
            e = e->next;
        }
    }
}

void trim_special(char *word) {
    if (word == NULL) return;

    int len = strlen(word);

    for (int i = len - 1; i >= 0; i--) {
        if (ispunct((unsigned int)word[i])) {
            word[i] = '\0';
        } else {
            word[i] = tolower(word[i]);
        }
    }
}

void count_words(struct HT *ht, char *filename) {
    FILE *f = fopen(filename, "r");
    char word[256];

    if (f == NULL) return;

    while(fscanf(f, "%s", word) == 1) {
        trim_special(word);
        insert(ht, word);
    }
}