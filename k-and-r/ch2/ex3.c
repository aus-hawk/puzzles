#include <ctype.h>
#include <stdio.h>

int htoi(char str[]);
int hex(char c);

int main(int argc, char *argv[]) {
    printf("%d\n", htoi(argv[1]));
    return 0;
}

int htoi(char s[]) {
    int n = 0;
    int i = 0;
    if (s[0] == '0' && tolower(s[1]) == 'x') {
        // skip 0x
        i = 2;
    }
    for (; hex(s[i]) > 0; ++i) {
        n = (n * 0x10) + hex(s[i]);
    }
    return n;
}

int hex(char c) {
    char low = tolower(c);
    if (isdigit(c)) {
        return c - '0';
    } else if (low >= 'a' && low <= 'f') {
        return low - 'a' + 10;
    } else {
        return -1;
    }
}
