#include <ctype.h>
#include <stdio.h>

double atof(char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); ++i)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        ++i;
    }

    for (val = 0.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        ++i;
    }

    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E') {
        ++i;

        int exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') {
            ++i;
        }

        int exp = 0;
        for (; isdigit(s[i]); ++i) {
            exp = 10 * exp + (s[i] - '0');
        }

        for (; exp > 0; --exp) {
            if (exp_sign < 0) {
                power *= 10.0;
            } else {
                power /= 10.0;
            }
        }
    }

    return sign * val / power;
}

int main(int argc, char *argv[]) {
    printf("%f\n", atof(argv[1]));
    return 0;
}
