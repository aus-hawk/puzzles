#include <stdio.h>
#define MAXLINE 1000

int getl(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = getl(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

int getl(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

void reverse(char s[]) {
    int i, len;

    for (i = 0; s[i] != '\0'; ++i)
        ;
    len = i;
    if (len > 0) {
        --len;
        if (s[len] == '\n') {
            --len;
        }
        /* s[len] is last non-newline non-null */
        for (i = 0; i <= len / 2; ++i) {
            char c;
            c = s[i];
            s[i] = s[len - i];
            s[len - i] = c;
        }
    }
}
