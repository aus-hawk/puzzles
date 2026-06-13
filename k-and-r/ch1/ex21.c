#include <stdio.h>

#define TABSTOP 8

void printsp(int wsnum, int currcol);

int main(void) {
    int c;
    int wsc; /* whitespace count */
    int col; /* column of last char */
    wsc = col = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            /* add num chars remaining until next tabstop) */
            wsc += TABSTOP - (col % TABSTOP);
            /* up to next tabstop */
            col = (col / TABSTOP + 1) * TABSTOP;
        } else if (c == ' ') {
            ++wsc;
            ++col;
        } else {
            printsp(wsc, col);
            if (c == '\n') {
                wsc = col = 0;
            } else {
                wsc = 0;
                ++col;
            }
            putchar(c);
        }
    }

    return 0;
}

void printsp(int wsc, int col) {
    int lc; /* column of last non-whitespace */
    int i;
    lc = col - wsc;
    if (lc / TABSTOP < col / TABSTOP) {
        putchar('\t');
        wsc -= TABSTOP - (lc % TABSTOP);
    }
    for (i = 0; i < wsc / TABSTOP; ++i) {
        putchar('\t');
    }
    for (i = 0; i < wsc % TABSTOP; ++i) {
        putchar(' ');
    }
}
