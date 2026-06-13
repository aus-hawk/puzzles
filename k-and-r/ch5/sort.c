#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        numeric = 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort((void **)lineptr, 0, nlines - 1,
                  (numeric ? (int (*)(void *, void *))numcmp : (int (*)(void *, void *))strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quicksort(v, left, last - 1, comp);
    quicksort(v, last + 1, right, comp);
}

#include <stdlib.h>

int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines) {
    *lineptr = NULL;
    int numlines = 0;

    int c, i = 0;
    while ((c = getchar()) != EOF) {
        if (*lineptr == NULL) {
            *lineptr = malloc(MAXLEN);
        }
        if (numlines >= maxlines) {
            return -1;
        } else {
            (*lineptr)[i++] = c;
            if (c == '\n') {
                (*lineptr)[i] = '\0';
                *++lineptr = NULL;
                ++numlines;
                i = 0;
            }
        }
    }

    return numlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s", *lineptr++);
    }
}
