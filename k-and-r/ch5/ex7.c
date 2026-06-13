#include <stdio.h>
#include <string.h>

#define MEMSIZE 10000
#define MAXLINES 5000

int readlines(char *lineptr[], int nlines, char *p);

int main(void) {
    char memory[MEMSIZE];
    char *lineptr[MAXLINES];
    int nlines = readlines(lineptr, MAXLINES, memory);
    for (int i = 0; i < nlines; ++i) {
        printf("%s\n", lineptr[i]);
    }
    return 0;
}

#define MAXLEN 1000

int getl(char *s, int lim);

/* p is an array in which strings are stored consecutively */
int readlines(char *lineptr[], int maxlines, char *p) {
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = getl(line, MAXLEN)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len; // p is the index directly after the null character
        }
    }
    return nlines;
}

int getl(char *s, int lim) {
    char *os = s;
    char *slim = s + lim;
    int c;

    while (s < slim - 1 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }

    if (c == '\n') {
        *s++ = c;
    }

    *s = '\0';

    return s - os;
}
