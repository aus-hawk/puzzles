#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa2(int n, char s[], int w) {
    int i, sign;
    int largest_neg = 0;

    if ((sign = n) < 0) {
        n = -n;
    }
    if (n < 0) {
        // is largest negative
        n = -(n + 1);
        largest_neg = 1;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    if (largest_neg) {
        ++s[0];
    }
    while (i < w) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

int main(void) {
    char s[1000];
    itoa2(572, s, 8);
    printf("This should be padded, starting from the colon:%s\n", s);
    return 0;
}
