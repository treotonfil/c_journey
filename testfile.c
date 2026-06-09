#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student* stud(char *sname, int sgrade);

struct Student {
    char *name;
    int grade;
};

int main() {
    struct Student * s1 = stud("Jonathan", 1);

    printf("%s has grade %d\n", s1->name, s1->grade);
    free(s1->name);
    free(s1);
    s1 = NULL;

    return 0;
}

struct Student* stud(char *sname, int sgrade) {
    struct Student * s1 = malloc(sizeof(struct Student));

    if (s1 == NULL) {
        printf("Failed");
        return NULL;
    }

    s1->name = strdup(sname);
    s1->grade = sgrade;

    return s1;
}