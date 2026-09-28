// Lab 3 — LL(1) Parser
// Question: Write a C program to implement an LL(1) parser for the grammar from Lab 2 and display its parsing actions. Here, i represents an identifier.

#include <stdio.h>
#include <ctype.h>

char input[100], stack[200];
int top = -1, pos = 0;

void push(char c) { stack[++top] = c; }

int main(void) {
    char x, look;
    const char *rule;

    printf("Enter expression: ");
    scanf("%99s", input);

    push('$');
    push('E');
    printf("Action\n------\n");

    while (top >= 0) {
        x = stack[top--];
        look = isalpha((unsigned char)input[pos]) ? 'i' :
               input[pos] ? input[pos] : '$';
        rule = NULL;

        if (x == 'i' || x == '+' || x == '*' ||
            x == '(' || x == ')' || x == '$') {
            if (x != look) break;
            printf("Match %c\n", look);
            if (x == '$') {
                puts("Input is successfully parsed.");
                return 0;
            }
            pos++;
            continue;
        }

        if (x == 'E' && (look == 'i' || look == '(')) {
            push('A'); push('T'); rule = "E -> TA";
        } else if (x == 'A' && look == '+') {
            push('A'); push('T'); push('+'); rule = "A -> +TA";
        } else if (x == 'A' && (look == ')' || look == '$')) {
            rule = "A -> epsilon";
        } else if (x == 'T' && (look == 'i' || look == '(')) {
            push('B'); push('F'); rule = "T -> FB";
        } else if (x == 'B' && look == '*') {
            push('B'); push('F'); push('*'); rule = "B -> *FB";
        } else if (x == 'B' &&
                   (look == '+' || look == ')' || look == '$')) {
            rule = "B -> epsilon";
        } else if (x == 'F' && look == 'i') {
            push('i'); rule = "F -> id";
        } else if (x == 'F' && look == '(') {
            push(')'); push('E'); push('('); rule = "F -> (E)";
        } else {
            break;
        }
        puts(rule);
    }

    puts("Input is rejected.");
    return 0;
}