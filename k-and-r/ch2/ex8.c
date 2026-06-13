#include <stdio.h>

unsigned char rightrot(unsigned char x, int n);

int main(void) {
    printf("%x\n", rightrot(0xF0, 3));
    printf("%x\n", rightrot(0x0F, 2));
    return 0;
}

unsigned char rightrot(unsigned char x, int n) {
    int char_bits = 0;
    for (unsigned char i = ~0; i > 0; i >>= 1) {
        ++char_bits;
    }
    unsigned char left_bits = (x & ~(~0 << n)) << (char_bits - n);
    unsigned char right_bits = x >> n;
    return left_bits | right_bits;
}
