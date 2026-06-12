#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void parse(char *input, char **args, int max_args);

int main() {
    char input[256];
    char *args[64];

    while (1) {
        printf("shell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        parse(input, args, 64);

        if (args[0] == NULL) continue;
        if (strcmp(args[0], "exit") == 0) break;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            printf("Command not found: %s\n", args[0]);
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}

void parse(char *input, char **args, int max_args) {
    char *token = strtok(input, " ");

    for (int i = 0; i < max_args; i++) {

        if (token == NULL) {
            args[i] = NULL;
            break;
        }

        args[i] = token;
        token = strtok(NULL, " ");
    }
    args[max_args - 1] = NULL;
}