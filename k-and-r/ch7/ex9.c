#include <stdio.h>
#include <ctype.h>

int isupper_space(int c) {
    return c >= 'A' && c <= 'Z';
}

int isupper_time(int c) {
    return (int[]){
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    }[c];
}

int main(void) {
    for (char c = ' '; c < 0x7f; ++c) {
        printf("%c, isupper: %d, isupper_space: %d, isupper_time: %d\n",
            c, isupper(c), isupper_space(c), isupper_time(c));
    }

    return 0;
}
