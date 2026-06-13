#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int minscanf(char *fmt, ...) {
    va_list ap;
    int *iptr;
    float *fptr;
    char *cptr;

    int scanned = 0;
    va_start(ap, fmt);
    for (; *fmt; ++fmt) {
        if (*fmt != '%') {
            int c;
            if (!isspace(c = getchar()) && c != *fmt) {
                return scanned;
            }
            continue;
        }
        switch (*++fmt) {
        case 'd':
            iptr = va_arg(ap, int *);
            scanned += scanf("%d", iptr);
            break;
        case 'f':
            fptr = va_arg(ap, float *);
            scanned += scanf("%f", fptr);
            break;
        case 'c':
            cptr = va_arg(ap, char *);
            scanned += scanf("%c", cptr);
            break;
        }
    }
    va_end(ap);

    return scanned;
}

int main(void) {
    int i;
    float f;
    char c;

    minscanf("%d %f %c", &i, &f, &c);
    printf("%d, %f, %c\n", i, f, c);

    return 0;
}
