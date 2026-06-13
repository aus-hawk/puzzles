#include <ctype.h>
#include <stdio.h>

int getfloat(double *);

int main(void) {
    double n;
    while (getfloat(&n) > 0) {
        printf("float found: %f\n", n);
    }
    printf("no more consecutive floats\n");
    return 0;
}

int getch(void);
void ungetch(int);

int getfloat(double *pn) {
    int c, sign;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int pm = c;
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            ungetch(pm);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    if (c == '.') {
        double power = 1.0;
        for (c = getch(); isdigit(c); c = getch()) {
            *pn = 10 * *pn + (c - '0');
            power *= 10;
        }
        *pn /= power;
    }
    *pn *= sign;
    if (c == EOF) {
        ungetch(c);
    }
    return c;
}

/*--- (un)getch ---*/

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
