#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact *new_contact(char *name, char *phone);
void print_contacts(struct Contact *head);
void append_contact(struct Contact **head, char *name, char *phone);
void free_contacts(struct Contact *head);
void delete_contact_by_name(struct Contact **head, char *name);
struct Contact *find_contact_by_name(struct Contact *head, char *name);
void save_contacts(struct Contact *head, char *filename);
void load_contacts(struct Contact **head, char *filename);


struct Contact {
    char *name;
    char *number;
    struct Contact *next;
};

int main() {
    struct Contact *contacts = NULL;
    struct Contact *feta = NULL;

    append_contact(&contacts, "John Doe", "767575");
    append_contact(&contacts, "Serana", "88498834");
    append_contact(&contacts, "Ming", "88498834");
    append_contact(&contacts, "Serana", "88498834");
    print_contacts(contacts);
    delete_contact_by_name(&contacts, "Ming");

    save_contacts(contacts, "contacts.txt");
    load_contacts(&feta, "contacts.txt");

    print_contacts(feta);

    free_contacts(contacts);
    free_contacts(feta);
    return 0;
}


struct Contact *new_contact(char *name, char *phone) {
    struct Contact *new = malloc(sizeof(struct Contact));

    if (new == NULL){
        return NULL;
    }

    new->name = strdup(name);
    new->number = strdup(phone);
    new->next = NULL;

    return new;
}

void free_contacts(struct Contact *head) {
    while (head != NULL) {
        struct Contact *temp = head->next;
        free(head->name);
        free(head->number);
        free(head);
        head = temp;
    }
}

void print_contacts(struct Contact *head) {
    while (head != NULL) {
        printf("%s: %s\n", head->name, head->number);
        head = head->next;
    }
}

struct Contact *find_contact_by_name(struct Contact *head, char *name) {
    while (head != NULL){
        if (strcmp(head->name, name) == 0) return head;
        head = head->next;
    }
    return NULL;
}

void append_contact(struct Contact **head, char *name, char *phone) {
    if (find_contact_by_name(*head, name) != NULL) {
    } else if (*head == NULL) {
        *head = new_contact(name, phone);
    } else {
        struct Contact *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_contact(name, phone);
    }
}

void delete_contact_by_name(struct Contact **head, char *name) {
    if (*head == NULL || find_contact_by_name(*head, name) == NULL) {
    } else if (strcmp((*head)->name, name) == 0){
        struct Contact *temp = *head;
        *head = (*head)->next;
        free_contacts(temp);
    } else {
        struct Contact *current = *head;
        while(current->next != NULL && strcmp(current->next->name, name) != 0){
            current = current->next;
        }
        struct Contact *temp = current->next;
        current->next = current->next->next;
        free_contacts(temp);
    }
}

void save_contacts(struct Contact *head, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f != NULL) {
        while (head != NULL) {
            fprintf(f, "%s,%s\n", head->name, head->number);
            head = head->next;
        }
        fclose(f);
    }
}

void load_contacts(struct Contact **head, char *filename) {
    FILE *f = fopen(filename, "r");
    char line[256];
    
    if (f != NULL) {
        while (fgets(line, sizeof(line), f) != NULL) {

            char *name = strtok(line, ",");
            char *number = strtok(NULL, "\n");
  
            append_contact(head, name, number);
        }
        fclose(f);
    }
}