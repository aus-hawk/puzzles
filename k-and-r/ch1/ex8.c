#include <stdio.h>

int main(void) {
    long blanks, tabs, newlines;

    blanks = 0;
    tabs = 0;
    newlines = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        }
        if (c == '\t') {
            ++tabs;
        }
        if (c == '\n') {
            ++newlines;
        }
    }

    printf("blanks: %ld\ttabs: %ld\tnewlines: %ld\n", blanks, tabs, newlines);

    return 0;
}

