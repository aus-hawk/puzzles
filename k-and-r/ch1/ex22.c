#include <stdio.h>

#define LINE_LIMIT 10
#define TABSTOP 8

int main(void) {
    int c;
    int col;                   /* column of last char */
    int wi;                    /* word index */
    char word[LINE_LIMIT + 1]; /* +1 to account for null terminator */
    col = wi = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            /* print stored word */
            word[wi] = '\0';
            printf("%s", word);
            wi = 0;
            /* print whitespace */
            putchar(c);
            if (c == ' ') {
                ++col;
            } else if (c == '\t') {
                col = (col / TABSTOP + 1) * TABSTOP;
            } else if (c == '\n') {
                col = 0;
            }
        } else {
            /* only worry about the line limit on non-whitespace */
            if (col >= LINE_LIMIT) {
                if (wi >= LINE_LIMIT) {
                    word[wi] = '\0';
                    printf("%s-", word);
                    wi = 0;
                }
                putchar('\n');
                col = wi;
            }

            word[wi] = c;
            ++wi;
            ++col;
        }
    }

    return 0;
}
