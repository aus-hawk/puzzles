#include <stdio.h>

#define TABSTOP 8

int main(void) {
    int c;
    int ts; /* number of chars after last tab stop */
    ts = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            while (ts < TABSTOP) {
                ++ts;
                putchar(' ');
            }
            ts = 0;
        } else if (c == '\n') {
            ts = 0;
            putchar(c);
        } else {
            ++ts;
            putchar(c);
            if (ts >= TABSTOP) {
                ts = 0;
            }
        }
    }

    return 0;
}
