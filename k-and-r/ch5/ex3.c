#include <stdio.h>

void pstrcat(char *s, char *t);

int main(int argc, char *argv[]) {
    char s[100] = "abcde";
    char *t = "fghij";
    pstrcat(s, t);
    printf("%s\n", s);
    return 0;
}

void pstrcat(char *s, char *t) {
    while (*s != '\0') {
        s++;
    }
    while ((*s++ = *t++) != '\0')
        ;
}
