#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypter(char *text, int shift);
void decrypt(char *text, int shift);

int main() {
    char input[256];
    int i;
    printf("Text >> ");
    fgets(input, sizeof(input), stdin);
    printf("Shift >> ");
    scanf("%d", &i);
    encrypter(input, i);
    printf("En: %s", input);
    decrypt(input, i);
    printf("De: %s", input);
    return 0;
}

void encrypter(char *text, int shift) {
    if (text == NULL) return;

    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        if (ispunct(text[i]) || isspace(text[i])) {
            continue;
        }  
        if (text[i] >= 'a') {
            int pos = text[i] - 'a';
            int shifted = (pos + shift) % 26;
            text[i] = shifted + 'a';
        } else {
            int pos = text[i] - 'A';
            int shifted = (pos + shift) % 26;
            text[i] = shifted + 'A';
        }
    }
}

void decrypt(char *text, int shift) {
    if (text == NULL) return;

    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        if (ispunct(text[i]) || isspace(text[i])) {
            continue;
        }
        if (text[i] >= 'a') {
            int pos = text[i] - 'a';
            int shifted = (pos - shift + 26) % 26;
            text[i] = shifted + 'a';
        } else {
            int pos = text[i] - 'A';
            int shifted = (pos - shift + 26) % 26;
            text[i] = shifted + 'A';
        }
    }
}