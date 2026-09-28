// Lab 7 — Machine Code Generation
// Question: Write a C program to generate simple machine instructions for an arithmetic expression. The instructions here are illustrative assembly, as in the supplied lab, rather than binary machine code.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0, count = 0;

char *expression(void);

char *operand(char c) {
    char *s = malloc(2);
    s[0] = c;
    s[1] = '\0';
    return s;
}

char *emit(char *left, char op, char *right) {
    char *temp = malloc(20);
    sprintf(temp, "t%d", ++count);
    printf("LOAD  R0, %s\n", left);
    printf("%-5s R0, %s\n",
           op == '+' ? "ADD" : op == '-' ? "SUB" :
           op == '*' ? "MUL" : "DIV", right);
    printf("STORE %s, R0\n", temp);
    return temp;
}

char *factor(void) {
    if (input[pos] == '(') {
        pos++;
        char *v = expression();
        if (input[pos] != ')') return NULL;
        pos++;
        return v;
    }
    if (isalnum((unsigned char)input[pos]))
        return operand(input[pos++]);
    return NULL;
}

char *term(void) {
    char *left = factor();
    while (left && (input[pos] == '*' || input[pos] == '/')) {
        char op = input[pos++];
        char *right = factor();
        if (!right) return NULL;
        left = emit(left, op, right);
    }
    return left;
}

char *expression(void) {
    char *left = term();
    while (left && (input[pos] == '+' || input[pos] == '-')) {
        char op = input[pos++];
        char *right = term();
        if (!right) return NULL;
        left = emit(left, op, right);
    }
    return left;
}

int main(void) {
    printf("Enter expression: ");
    scanf("%99s", input);
    puts("Generated instructions:");
    char *result = expression();
    if (!result || input[pos] != '\0')
        puts("Invalid expression.");
    return 0;
}