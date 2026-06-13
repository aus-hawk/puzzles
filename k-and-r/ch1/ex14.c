#include <stdio.h>

#define MAX_ASCII_VAL 128

int main(void) {
    int c, i, j;
    int cfreqs[MAX_ASCII_VAL];

    for (i = 0; i < MAX_ASCII_VAL; ++i) {
        cfreqs[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c < MAX_ASCII_VAL) {
            ++cfreqs[c];
        }
    }

    for (i = 0; i < MAX_ASCII_VAL; ++i) {
        if (cfreqs[i] > 0) {
            if (i <= ' ') {
                printf("<%2d>: ", i);
            } else {
                printf("%c   : ", i);
            }
            for (j = 0; j < cfreqs[i]; ++j) {
                putchar('*');
            }
            putchar('\n');
        }
    }

    return 0;
}
