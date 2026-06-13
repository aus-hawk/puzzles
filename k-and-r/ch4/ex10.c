#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int getl(void);

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    getl();

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0) {
                push(pop() / op2);
            } else {
                printf("error: zero divisor\n");
            }
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}

/*--- stack ---*/

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/*--- getop ---*/

#include <ctype.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getop(char s[]) {
    if (buf[bufp] == '\0') {
        getl();
    }
    int i, c;

    while ((s[0] = c = buf[bufp++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = buf[bufp++]))
            ;
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = buf[bufp++]))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        --bufp;
    }
    return NUMBER;
}

/*--- getch and ungetch ---*/

int getl(void) {
    int c, i;
    bufp = 0;

    for (i = 0; i < BUFSIZE - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        buf[i] = c;
    }
    buf[i++] = c;
    buf[i] = '\0';
    return i;
}
