#include <stdio.h>

void pstrncpy(char *s, char *t, int n);
void pstrncat(char *s, char *t, int n);
int pstrncmp(char *s, char *t, int n);

int main(int argc, char *argv[]) {
    char str[100] = "abc";
    printf("init: %s (n = 5)\n", str);

    pstrncpy(str, argv[1], 5);
    printf("pstrncpy: %s\n", str);

    pstrncat(str, argv[2], 5);
    printf("pstrncpy: %s\n", str);

    printf("pstrncmp: %d\n", pstrncmp(str, argv[3], 5));

    return 0;
}

void pstrncpy(char *s, char *t, int n) {
    char *lim = s + n;
    while (s < lim && *t != '\0') {
        *s++ = (*t == '\0') ? '\0' : *t++;
    }
}

void pstrncat(char *s, char *t, int n) {
    for (; *s != '\0'; ++s)
        ;

    char *lim = t + n;

    while (t < lim && *t != '\0') {
        *s++ = *t++;
    }
    *s = '\0';
}

int pstrncmp(char *s, char *t, int n) {
    char *lim = s + n;

    for (; s < lim && *s != '\0'; ++s, ++t) {
        if (*s != *t) {
            return *s - *t;
        }
    }

    return (s < lim) ? *s - *t : 0;
}
