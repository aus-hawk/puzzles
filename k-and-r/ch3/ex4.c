#include <stdio.h>
#include <string.h>

/*
 * The book's version of itoa cannot handle the largest negative number
 * represented with two's compliment because, if the number is negative, it is
 * negated before it is printed. In two's compliment, the largest positive
 * number is one less than the absolute value of the largest negative number.
 * Thus, there is no way to represent the absolute value of the largest negative
 * number in two's compliment. Negating the number results in the same negative
 * number, but the character generation code only expects positive numbers.
 */

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

void itoa2(int n, char s[]) {
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
    s[i] = '\0';
    if (largest_neg) {
        ++s[0];
    }
    reverse(s);
}

int main(void) {
    int largest_neg = ~0 ^ (~0u >> 1u);
    char s[1000];
    itoa2(largest_neg, s);
    printf("%d: %s\n", largest_neg, s);
    itoa(largest_neg, s);
    printf("bad: %s\n", s);
    return 0;
}
