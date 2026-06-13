#include <stdio.h>
#include <ctype.h>
#include "calc.h"

static int last_char;
static int has_last_char = 0;

int gch(void);
void ugch(int);

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = gch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = gch()))
            ;
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = gch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        ugch(c);
    }
    return NUMBER;
}

int gch(void) {
    if (has_last_char) {
        has_last_char = 0;
        return last_char;
    } else {
        return getch();
    }
}

void ugch(int c) {
    last_char = c;
    has_last_char = 1;
}
