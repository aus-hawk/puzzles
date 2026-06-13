#include <ctype.h>
#include <stdio.h>

int main(void) {
    int c;
    int col = 0;
    while ((c = getchar()) != EOF) {
        if (!isgraph(c)) {
            printf("0x%02x", c);
            if (c == '\n') {
                putchar(c);
                col = 0;
            } else {
                col += 4;
            }
        } else {
            if (col++ > 80) {
                putchar('\n');
                col = 1;
            }
            putchar(c);
        }
    }

    return 0;
}
