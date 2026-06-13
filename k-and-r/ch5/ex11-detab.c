#include <stdio.h>
#include <stdlib.h>

#define MAX_TAB_STOPS 100
#define DEFAULT_TAB_STOP 8

int main(int argc, char *argv[]) {
    int tab_stops[MAX_TAB_STOPS];
    int *tab_stop = tab_stops;
    if (argc == 1) {
        for (int i = 1; i <= MAX_TAB_STOPS; ++i) {
            *tab_stop++ = DEFAULT_TAB_STOP * i;
        }
    } else {
        while (argc-- > 1) {
            *tab_stop++ = atoi(*++argv);
        }
    }
    tab_stop = tab_stops;

    int c;
    int col = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            while (col < *tab_stop) {
                putchar(' ');
                ++col;
            }
        } else if (c == '\n') {
            col = 0;
            tab_stop = tab_stops;
            putchar(c);
        } else {
            ++col;
            putchar(c);
        }

        while (col >= *tab_stop) {
            ++tab_stop;
        }
    }

    return 0;
}
