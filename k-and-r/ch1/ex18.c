#include <stdio.h>
#define MAXLINE 1000

int getl(char line[], int maxline);
void copy(char to[], char from[]);
void rmtrail(char to[], char from[]);

int main(void) {
    int len;
    char line[MAXLINE], out[MAXLINE];

    while ((len = getl(line, MAXLINE)) > 0) {
        rmtrail(out, line);
        printf("%s", out);
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

void rmtrail(char to[], char from[]) {
    int i;

    for (i = 0; from[i] != '\0'; ++i) {
        to[i] = from[i];
    }

    --i;
    /* to[i] is now last character */
    while (i >= 0 && (to[i] == ' ' || to[i] == '\t' || to[i] == '\n')) {
        --i;
    }

    /* to[i] is now last non-whitespace character or i == -1 */
    ++i;

    if (i > 0) {
        to[i] = '\n';
        ++i;
    }

    to[i] = '\0';
}
