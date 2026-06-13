#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main(int argc, char *argv[]) {
    reverse(argv[1]);
    printf("%s\n", argv[1]);
    return 0;
}

void reverse2(char s[], int length, int i) {
    char temp;
    temp = s[i];
    s[i] = s[length - i - 1];
    s[length - i - 1] = temp;
    if (i < length / 2 - 1) {
        reverse2(s, length, i + 1);
    }
}

void reverse(char s[]) { reverse2(s, strlen(s), 0); }
