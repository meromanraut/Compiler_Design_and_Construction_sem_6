// Lab 4 — Shift–Reduce Parser
// Question: Write a C program to show shifting and reduction using E → E+E | E*E | (E) | id.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100], stack[100];
int top = -1, pos = 0;

void show(const char *action) {
    stack[top + 1] = '\0';
    printf("%-12s %-12s %s\n", stack, input + pos, action);
}

int reduce(void) {
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        show("Reduce E -> id");
        return 1;
    }
    if (top >= 2 && stack[top-2] == '(' &&
        stack[top-1] == 'E' && stack[top] == ')') {
        top -= 2;
        stack[top] = 'E';
        show("Reduce E -> (E)");
        return 1;
    }
    if (top >= 2 && stack[top-2] == 'E' &&
        stack[top] == 'E' &&
        (stack[top-1] == '+' || stack[top-1] == '*')) {
        char op = stack[top-1];
        top -= 2;
        stack[top] = 'E';
        show(op == '+' ? "Reduce E -> E+E" : "Reduce E -> E*E");
        return 1;
    }
    return 0;
}

int main(void) {
    printf("Enter expression: ");
    scanf("%99s", input);
    printf("%-12s %-12s %s\n", "Stack", "Input", "Action");

    while (input[pos]) {
        char c = input[pos++];
        if (isalpha((unsigned char)c)) c = 'i';
        stack[++top] = c;
        show("Shift");
        while (reduce()) {}
    }

    puts(top == 0 && stack[0] == 'E'
         ? "Input is successfully parsed."
         : "Input is rejected.");
    return 0;
}