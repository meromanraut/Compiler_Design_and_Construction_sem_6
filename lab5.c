// Lab 5 — Three Address Code Generation
// Question: Write a C program to generate three address code for an arithmetic expression.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0, count = 0;

char *expression(void);

char *name(char c) {
    char *s = malloc(2);
    s[0] = c;
    s[1] = '\0';
    return s;
}

char *generate(char *left, char op, char *right) {
    char *temp = malloc(20);
    sprintf(temp, "t%d", ++count);
    printf("%s = %s %c %s\n", temp, left, op, right);
    return temp;
}

char *factor(void) {
    if (input[pos] == '(') {
        pos++;
        char *value = expression();
        if (input[pos] != ')') return NULL;
        pos++;
        return value;
    }
    if (isalnum((unsigned char)input[pos]))
        return name(input[pos++]);
    return NULL;
}

char *term(void) {
    char *left = factor();
    while (left && (input[pos] == '*' || input[pos] == '/')) {
        char op = input[pos++];
        char *right = factor();
        if (!right) return NULL;
        left = generate(left, op, right);
    }
    return left;
}

char *expression(void) {
    char *left = term();
    while (left && (input[pos] == '+' || input[pos] == '-')) {
        char op = input[pos++];
        char *right = term();
        if (!right) return NULL;
        left = generate(left, op, right);
    }
    return left;
}

int main(void) {
    printf("Enter expression: ");
    scanf("%99s", input);
    puts("Three address code:");
    char *result = expression();
    if (!result || input[pos] != '\0')
        puts("Invalid expression.");
    return 0;
}