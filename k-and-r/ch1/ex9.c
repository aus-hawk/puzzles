#include <stdio.h>

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            putchar(' ');
            while ((c = getchar()) == ' ')
                ;
        }
        putchar(c);
    }

    return 0;
}
