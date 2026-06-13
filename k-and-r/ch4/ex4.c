#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);
void clear(void);

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

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
        case '%':
            op2 = pop();
            if (op2 != 0.0) {
                push((int)pop() % (int)op2);
            } else {
                printf("error: zero divisor\n");
            }
            break;
        case 'p':
            op2 = pop();
            printf("\t%.8g\n", op2);
            push(op2);
            break;
        case 'd':
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case 's': {
            double op1 = pop();
            op2 = pop();
            push(op1);
            push(op2);
            break;
        }
        case 'c':
            clear();
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

void clear(void) {
    sp = 0;
}

/*--- getop ---*/

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int i, c, is_num, op;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
        return c;
    } else if (c == '+' || c == '-') {
        op = c;
        s[++i] = c = getch();
    }
    is_num = 0;
    if (isdigit(c)) {
        is_num = 1;
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    if (c == '.') {
        is_num = 1;
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return is_num ? NUMBER : op;
}

/*--- getch and ungetch ---*/

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
