#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *lineptr[], int left, int right);
int numcmp(char *, char *);
int istrcmp(char *, char *);

#define MAXFIELDS 10

int numfields = 0;

int (*comp[MAXFIELDS])(void *, void *);
int fold[MAXFIELDS] = {0};
int dir[MAXFIELDS] = {0};

int compfields(char *, char *);

int main(int argc, char *argv[]) {
    int nlines;

    for (int i = 0; i < MAXFIELDS; ++i) {
        comp[i] = (int (*)(void *, void *))strcmp;
    }

    for (int arg = 1; arg < argc; ++arg) {
        if (argv[arg][0] == '-') {
            for (int flag = 1; argv[arg][flag] != '\0'; ++flag) {
                switch (argv[arg][flag]) {
                case 'n':
                    comp[arg - 1] = (int (*)(void *, void *))numcmp;
                    break;
                case 'f':
                    comp[arg - 1] = (int (*)(void *, void *))istrcmp;
                    fold[arg - 1] = 1;
                    break;
                case 'd':
                    comp[arg - 1] = (int (*)(void *, void *))istrcmp;
                    dir[arg - 1] = 1;
                    break;
                }
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort((void **)lineptr, 0, nlines - 1);
        printf("\nSorted output:\n\n");
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void quicksort(void *v[], int left, int right) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (compfields(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}

#define MAXLEN 1000

int field;

int compfields(char *left, char *right) {
    char lf[MAXLEN], rf[MAXLEN];

    for (field = 0; field < MAXFIELDS && *left != '\0' && *right != '\0'; ++field) {
        int i;
        for (i = 0; *left != '\t' && *left != '\0'; ++i) {
            lf[i] = *left++;
        }
        lf[i] = '\0';
        if (*left == '\t') {
            ++left;
        }

        for (i = 0; *right != '\t' && *right != '\0'; ++i) {
            rf[i] = *right++;
        }
        rf[i] = '\0';
        if (*right == '\t') {
            ++right;
        }

        int diff;
        if ((diff = (*comp[field])(lf, rf)) != 0) {
            return diff;
        }
    }

    return *left - *right;
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

#include <ctype.h>

int istrcmp(char *s1, char *s2) {
    while (*s1 != '\0') {
        if (dir[field]) {
            while (!isalnum(*s1) && !isblank(*s1)) {
                ++s1;
            }
            while (!isalnum(*s2) && !isblank(*s2)) {
                ++s2;
            }
        }

        char c1 = *s1, c2 = *s2;
        if (fold[field]) {
            c1 = tolower(c1);
            c2 = tolower(c2);
        }

        if (c1 != c2) {
            return c1 - c2;
        }

        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

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
