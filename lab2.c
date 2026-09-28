// Lab 2 — Recursive Descent Parser
// Question: Write a C program to implement a recursive descent parser 
// for E → TA, A → +TA | ε, T → FB, B → *FB | ε, and F → (E) | id.

#include <stdio.h>
#include <ctype.h>

char input[100];
int pos = 0;

int E(void);
int T(void);
int F(void);

int E(void) {
    if (!T()) return 0;
    while (input[pos] == '+') {
        pos++;
        if (!T()) return 0;
    }
    return 1;
}

int T(void) {
    if (!F()) return 0;
    while (input[pos] == '*') {
        pos++;
        if (!F()) return 0;
    }
    return 1;
}

int F(void) {
    if (isalpha((unsigned char)input[pos])) {
        pos++;
        return 1;
    }
    if (input[pos] == '(') {
        pos++;
        if (!E() || input[pos] != ')') return 0;
        pos++;
        return 1;
    }
    return 0;
}

int main(void) {
    printf("Enter expression: ");
    scanf("%99s", input);

    if (E() && input[pos] == '\0')
        puts("Input is successfully parsed.");
    else
        puts("Input is rejected.");
    return 0;
}