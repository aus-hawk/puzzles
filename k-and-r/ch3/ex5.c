#include <ctype.h>
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

char to_digit(int c) {
    return (c < 10) ? (c + '0') : (c - 10 + 'a');
}

int from_digit(char c) {
    return isdigit(c) ? (c - '0') : (c + 10 - 'a');
}

void itob(int n, char s[], int b) {

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
        s[i++] = to_digit(n % b);
    } while ((n /= b) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    if (largest_neg) {
        s[0] = to_digit(from_digit(s[0]) + 1);
    }
    reverse(s);
}

int main(void) {
    char s[1000];
    int n = 0xcf04;
    itob(n, s, 16);
    printf("%x: %s\n", n, s);
    return 0;
}
