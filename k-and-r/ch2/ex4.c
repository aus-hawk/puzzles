#include <stdio.h>

void squeeze(char str[], char cs[]);
int contains(char s[], char c);

int main(int argc, char *argv[]) {
    squeeze(argv[1], argv[2]);
    printf("%s\n", argv[1]);
    return 0;
}

void squeeze(char s1[], char s2[]) {
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++) {
        if (!contains(s2, s1[i])) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

int contains(char s[], char c) {
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}
