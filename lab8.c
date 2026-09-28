// Lab 8 — Front End of a Compiler
// Question: Create a compiler front end in C that performs lexical analysis, syntax analysis, and three address code generation.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0, count = 0;

char *expression(void);

void lexical_analysis(void) {
    puts("\nLEXICAL ANALYSIS");
    for (int i = 0; input[i]; i++) {
        char c = input[i];
        if (isalpha((unsigned char)c))
            printf("%c -> Identifier\n", c);
        else if (isdigit((unsigned char)c))
            printf("%c -> Constant\n", c);
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            printf("%c -> Operator\n", c);
        else if (c == '(' || c == ')')
            printf("%c -> Special Symbol\n", c);
        else
            printf("%c -> Unknown\n", c);
    }
}

char *operand(char c) {
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
        return operand(input[pos++]);
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
    printf("Enter arithmetic expression: ");
    scanf("%99s", input);

    lexical_analysis();
    puts("\nSYNTAX ANALYSIS AND THREE ADDRESS CODE");
    char *result = expression();

    if (result && input[pos] == '\0')
        puts("Input is syntactically correct.");
    else
        puts("Syntax error: invalid expression.");
    return 0;
}