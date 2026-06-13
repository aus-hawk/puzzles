#include <stdio.h>

#define MAXLINE 100

void getl(char *s, int lim);

int main(void) {
    char input[MAXLINE];
    getl(input, MAXLINE);
    printf("%s\n", input);
    return 0;
}

void getl(char *s, int lim) {
    char *slim = s + lim;
    int c;

    while (s < slim - 1 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }

    if (c == '\n') {
        *s++ = c;
    }

    *s = '\0';
}
