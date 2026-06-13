#include <stdio.h>
#include <limits.h>

int main(void) {
    unsigned char max_uchar = 0;
    max_uchar -= 1;
    unsigned short max_ushort = 0;
    max_ushort -= 1;
    unsigned int max_uint = 0;
    max_uint -= 1;
    unsigned long max_ulong = 0;
    max_ulong -= 1;
    printf("unsigned char: %d - %d", 0, max_uchar);
    printf("unsigned short: %d - %d", 0, max_ushort);
    printf("unsigned int: %d - %d", 0, max_uint);
    printf("unsigned long: %ld - %ld", 0l, max_ulong);

    signed char min_schar, max_schar;
    signed short min_sshort, max_sshort;
    signed int min_sint, max_sint;
    signed long min_lint, max_lint;
    printf("signed char: %d - %d");
    printf("signed short: %d - %d");
    printf("signed int: %d - %d");
    printf("signed long: %d - %d");

    return 0;
}
