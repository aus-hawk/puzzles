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
    int spaces = 0;
    while ((c = getchar()) != EOF) {
        if (spaces != 0) {
            if (col + spaces == *tab_stop) {
                putchar('\t');
                spaces = 0;
                col = *tab_stop++;
            } else if (c != ' ' && c != '\t') {
                col += spaces;
                for (; spaces > 0; --spaces) {
                    putchar(' ');
                }
            }
        }
        switch (c) {
        case '\t':
            putchar('\t');
            col = *tab_stop++;
            spaces = 0;
            break;
        case ' ':
            ++spaces;
            break;
        case '\n':
            putchar('\n');
            col = 0;
            tab_stop = tab_stops;
            break;
        default:
            putchar(c);
            if (++col == *tab_stop) {
                ++tab_stop;
            }
            break;
        }
    }

    return 0;
}
