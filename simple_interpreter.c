#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    double value;
} Token;

typedef struct ASTNode {
    TokenType type;
    double value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

void tokenize(char *input, Token *tokens, int *count);
ASTNode *create_node(Token token);
ASTNode *parse_expression(Token *tokens, int *pos);
ASTNode *parse_term(Token *tokens, int *pos);
ASTNode *parse_primary(Token *tokens, int *pos);
double evaluate(ASTNode *node);

int main() {
    Token tokens[256];
    char input[256];
    int count = 0;
    int pos = 0;

    printf("GREG >> ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    tokenize(input, tokens, &count);
    ASTNode *tree = parse_expression(tokens, &pos);

    printf("= %f\n", evaluate(tree));
    printf("%d\n", count);

    return 0;
}

void tokenize(char *input, Token *tokens, int *count) {
    if (input == NULL) return;

    char *to;
    int len = strlen(input);

    for (int i = 0; i < len; i++) {

        if (isspace(input[i])) continue;

        if (isdigit(input[i])) {
            tokens[*count].type = TOKEN_NUMBER;
            tokens[*count].value = strtod(&input[i], &to);
            (*count)++;
            i = to - input - 1;
        } else {
            if (input[i] == '+') {
                tokens[*count].type = TOKEN_PLUS;
                (*count)++;
            } else if (input[i] == '-') {
                tokens[*count].type = TOKEN_MINUS;
                (*count)++;
            } else if (input[i] == '*') {
                tokens[*count].type = TOKEN_MULTIPLY;
                (*count)++;
            } else if (input[i] == '/') {
                tokens[*count].type = TOKEN_DIVIDE;
                (*count)++;
            }
        }
    }

    tokens[*count].type = TOKEN_EOF;
    (*count)++;
}

ASTNode *create_node(Token token) {
    struct ASTNode *node= malloc(sizeof(struct ASTNode));

    if (node == NULL) return NULL;

    node->type = token.type;
    node->value = token.value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

ASTNode *parse_primary(Token *tokens, int *pos) {
    if (tokens[*pos].type == TOKEN_NUMBER) {
        ASTNode *node = create_node(tokens[*pos]);
        (*pos)++;
        return node;
    }
    return NULL;
}

ASTNode *parse_term(Token *tokens, int *pos) {
    ASTNode *node_left = parse_primary(tokens, pos);
    ASTNode *node = NULL;
    Token token;
    while(tokens[*pos].type == TOKEN_MULTIPLY || tokens[*pos].type == TOKEN_DIVIDE) {
        token = tokens[*pos];
        (*pos)++;
        ASTNode *node_right = parse_primary(tokens, pos);
        node = create_node(token);
        node->left = node_left;
        node->right = node_right;
        node_left = node;
    }
    if (node == NULL) return node_left;
    return node;
}

ASTNode *parse_expression(Token *tokens, int *pos) {
    ASTNode *node_left = parse_term(tokens, pos);
    ASTNode *node = NULL;
    Token token;
    while (tokens[*pos].type == TOKEN_PLUS || tokens[*pos].type == TOKEN_MINUS) {
        token = tokens[*pos];
        (*pos)++;
        ASTNode *node_right = parse_term(tokens, pos);
        node = create_node(token);
        node->left = node_left;
        node->right = node_right;
        node_left = node;
    }
    if (node == NULL) return node_left;
    return node;
}

double evaluate(ASTNode *node) {
    return node->type == TOKEN_NUMBER
           ? node->value
           : node->type == TOKEN_PLUS
           ? evaluate(node->left) + evaluate(node->right)
           : node->type == TOKEN_MINUS
           ? evaluate(node->left) - evaluate(node->right)
           : node->type == TOKEN_MULTIPLY
           ? evaluate(node->left) * evaluate(node->right)
           : evaluate(node->left) / evaluate(node->right);
}