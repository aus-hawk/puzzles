#include <stdio.h>

void expand(char s1[], char s2[]);

int main(int argc, char *argv[]) {
    char c[1000];
    expand(argv[1], c);
    printf("%s\n", c);
    return 0;
}

void expand(char s1[], char s2[]) {
    int i, j;
    for (i = j = 0; s1[i] != '\0'; ++i) {
        if (s1[i + 1] == '-' && s1[i + 2] != '\0') {
            for (char c = s1[i]; c <= s1[i + 2]; ++c) {
                s2[j++] = c;
            }
            i += 2;
        } else {
            s2[j++] = s1[i];
        }
    }

    s2[j] = '\0';
}
