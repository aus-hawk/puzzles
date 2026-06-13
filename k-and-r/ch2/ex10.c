#include <stdio.h>

char lower(char c);

int main(int argc, char *argv[]) {
    for (int i = 0; argv[1][i] != '\0'; ++i) {
        putchar(lower(argv[1][i]));
    }
    putchar('\n');
    return 0;
}

char lower(char c) { return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c; }
