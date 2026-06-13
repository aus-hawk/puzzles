#include <stdio.h>

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        int flag;
        flag = 0;
        if (c == '\t') {
            printf("\\t");
            flag = 1;
        }
        if (c == '\b') {
            printf("\\b");
            flag = 1;
        }
        if (c == '\\') {
            printf("\\\\");
            flag = 1;
        }
        if (flag == 0) {
            putchar(c);
        }
    }

    return 0;
}
