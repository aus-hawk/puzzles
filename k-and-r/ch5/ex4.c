#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main(int argc, char *argv[]) {
    printf("%d\n", strend(argv[1], argv[2]));
    return 0;
}

int strend(char *s, char *t) {
    int slen = strlen(s);
    int tlen = strlen(t);

    if (slen < tlen) {
        return 0;
    }

    s += slen - tlen;

    while (*s != '\0' && *s == *t) {
        ++s;
        ++t;
    }

    return *s == *t;
}
