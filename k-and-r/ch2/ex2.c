#include <stdio.h>

int main(void) {
    int lim = 1000;
    int c;
    int i = 0;
    int flag = 1;
    while (flag) {
        flag = 0;
        if (i < lim - 1) {
            if ((c = getchar()) != '\n') {
                if (c != EOF) {
                    flag = 1;
                    ++i;
                }
            }
        }
    }
    return 0;
}
