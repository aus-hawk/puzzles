#include <stdio.h>

void itoa(char s[], int n);

int main(void) {
    char out[100];
    int n = 5376;
    itoa(out, n);
    printf("%d: %s\n", n, out);

    n = -12345;
    itoa(out, n);
    printf("%d: %s\n", n, out);

    return 0;
}

int itoa2(char s[], int n, int i) {
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10) {
        i = itoa2(s, n / 10, i);
    }

    s[i++] = n % 10 + '0';
    s[i] = '\0';

    return i;
}

void itoa(char s[], int n) {
    itoa2(s, n, 0);
}
