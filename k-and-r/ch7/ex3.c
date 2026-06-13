#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    char cval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch(*++p) {
        case 'd':
        case 'x':
            ival = va_arg(ap, int);
            printf((*p == 'd') ? "%d" : "%x", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++) {
                putchar(*sval);
            }
            break;
        case 'c':
            cval = va_arg(ap, int);
            printf("%c", cval);
            break;
        case '%':
            putchar('%');
            break;
        }
    }
    va_end(ap);
}

int main(void) {
    minprintf("%d%%. 0x%x, in other words. %s!\n", 40, 40, "ok");
    minprintf("%c%c%c%c%c world!\n", 'h', 'e', 'l', 'l', 'o');
}
