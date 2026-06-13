#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

int main(void) {
    printf("%x\n", invert(0x55, 6, 4));
    return 0;
}

unsigned int invert(unsigned int x, int p, int n) { return x ^ (~(~0 << n) << (p - n)); }
