// Lab 1 — Lexical Analyzer
// Question: Write a C program to identify keywords, identifiers, numbers, operators,
//  and special symbols in a source statement.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int keyword(const char *s) {
    const char *words[] = {
        "int", "float", "char", "double", "if",
        "else", "for", "while", "return", "void"
    };
    for (int i = 0; i < 10; i++)
        if (strcmp(s, words[i]) == 0) return 1;
    return 0;
}

int main(void) {
    char line[256], token[256];
    int i = 0, j;

    printf("Enter source statement: ");
    fgets(line, sizeof line, stdin);

    while (line[i]) {
        if (isspace((unsigned char)line[i])) {
            i++;
        } else if (isalpha((unsigned char)line[i]) || line[i] == '_') {
            j = 0;
            while (isalnum((unsigned char)line[i]) || line[i] == '_')
                token[j++] = line[i++];
            token[j] = '\0';
            printf("%s -> %s\n", token,
                   keyword(token) ? "Keyword" : "Identifier");
        } else if (isdigit((unsigned char)line[i])) {
            j = 0;
            while (isdigit((unsigned char)line[i]) || line[i] == '.')
                token[j++] = line[i++];
            token[j] = '\0';
            printf("%s -> Constant\n", token);
        } else if (strchr("+-*/%=<>", line[i])) {
            printf("%c -> Operator\n", line[i++]);
        } else if (strchr(";,(){}[]", line[i])) {
            printf("%c -> Special Symbol\n", line[i++]);
        } else {
            printf("%c -> Unknown\n", line[i++]);
        }
    }
    return 0;
}