#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void parse(char *input, char **args, int max_args);

int main() {
    char input[256];
    char *args[64];

    while (1) {
        printf("shell> ");
        fgets(input, sizeof(input), stdin);
        parse(input, args, 64);
        // strip line
        input[strcspn(input, "\n")] = '\0';
        printf("you typed: %s\n", input);
    }
}

void parse(char *input, char **args, int max_args) {

    for (int i = 0; i < max_args; i++) {

        char *token = strtok(input, " ");

        if (token == NULL) {
            args[i] = NULL;
            break;
        }

        args[i] = token;
        printf("%s", args[i]);
    }
}