#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

int main(void) {
    printf("%x\n", setbits(0x00, 6, 4, 0xFF));
    return 0;
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
    // Mask of n ones.
    unsigned int n_mask = ~(~0 << n);
    // Mask of n ones starting at position p.
    unsigned int x_mask = n_mask << (p - n);
    // First n bits of y shifted to start at position p.
    unsigned int y_bits_shifted = (y & n_mask) << (p - n);
    return (x & ~x_mask) | y_bits_shifted;
}
