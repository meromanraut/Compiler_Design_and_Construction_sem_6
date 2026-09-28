#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Single-letter operands; +, -, *, / and parentheses. */
typedef struct { char op; char a[12], b[12], result[12]; } Quad;
Quad q[50];
char expr[100], ops[100], postfix[100], values[100][12];
int ot = -1, n = 0, count = 0, vt = -1;

int prec(char c) { return (c == '*' || c == '/') ? 2 : 1; }
int main(void) {
    printf("Enter arithmetic expression: ");
    if (scanf("%99s", expr) != 1) return 1;
    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (isalnum((unsigned char)c)) postfix[n++] = c;
        else if (c == '(') ops[++ot] = c;
        else if (c == ')') {
            while (ot >= 0 && ops[ot] != '(') postfix[n++] = ops[ot--];
            if (ot < 0) { puts("Invalid expression."); return 1; }
            ot--;
        } else if (strchr("+-*/", c)) {
            while (ot >= 0 && ops[ot] != '(' && prec(ops[ot]) >= prec(c))
                postfix[n++] = ops[ot--];
            ops[++ot] = c;
        } else { puts("Invalid expression."); return 1; }
    }
    while (ot >= 0) {
        if (ops[ot] == '(') { puts("Invalid expression."); return 1; }
        postfix[n++] = ops[ot--];
    }
    for (int i = 0; i < n; i++) {
        char c = postfix[i];
        if (isalnum((unsigned char)c)) {
            values[++vt][0] = c; values[vt][1] = '\0';
        } else {
            if (vt < 1 || count >= 50) { puts("Invalid expression."); return 1; }
            q[count].op = c;
            strcpy(q[count].b, values[vt--]);
            strcpy(q[count].a, values[vt--]);
            snprintf(q[count].result, 12, "t%d", count + 1);
            strcpy(values[++vt], q[count].result);
            count++;
        }
    }
    if (vt != 0) { puts("Invalid expression."); return 1; }
    puts("Quadruples:");
    puts("No  Op  Arg1  Arg2  Result");
    for (int i = 0; i < count; i++)
        printf("%-3d %-3c %-5s %-5s %s\n", i, q[i].op, q[i].a, q[i].b, q[i].result);
    puts("Triples:");
    puts("No  Op  Arg1  Arg2");
    for (int i = 0; i < count; i++) {
        char a[12], b[12];
        strcpy(a, q[i].a); strcpy(b, q[i].b);
        for (int j = 0; j < i; j++) {
            if (strcmp(a, q[j].result) == 0) snprintf(a, sizeof a, "(%d)", j);
            if (strcmp(b, q[j].result) == 0) snprintf(b, sizeof b, "(%d)", j);
        }
        printf("%-3d %-3c %-5s %s\n", i, q[i].op, a, b);
    }
    return 0;
}
