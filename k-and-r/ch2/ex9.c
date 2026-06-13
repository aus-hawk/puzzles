/*
 * Subtracting one from a two's compliment binary number is equivalent to
 * flipping every bit from the right up to and including the first 1-bit. This
 * means that the bit string starting from the rightmost 1-bit is negated. A
 * bitwise & operation thus results in a 0-bit for all of the bits which were
 * flipped. The 0-bits are thus unchanged, and the only 1-bit (the rightmost of
 * the number) is &-ed with a 0-bit, necessarily resulting in a 0-bit where the
 * rightmost 1-bit was.
 */

#include <stdio.h>

int bitcount(unsigned int x);

int main(void) {
    printf("%d\n", bitcount(0x55));
    return 0;
}

int bitcount(unsigned int x) {
    int b;
    for (b = 0; x != 0; x &= (x - 1)) {
        ++b;
    }
    return b;
}
