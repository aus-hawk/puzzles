#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]) {
    for (int i = strlen(s); i >= 0; --i) {
        int j, k;
        for (j = i, k = 0; s[j] != '\0' && s[j] == t[k]; ++j, ++k)
            ;
        if (t[k] == '\0') {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    printf("%d\n", strrindex(argv[1], argv[2]));
    return 0;
}
