#include <stdio.h>

#define OUT 0
#define IN 1

int main(void) {
    int c, i, j, state, length;
    int lcounts[20];

    length = 0;
    state = OUT;

    for (i = 0; i < 20; ++i) {
        lcounts[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN && length > 0 && length <= 20) {
                ++lcounts[length - 1];
            }
            state = OUT;
            length = 0;
        } else {
            state = IN;
        }
        if (state == IN) {
            ++length;
        }
    }

    printf("Horizontal histogram:\n");

    for (i = 0; i < 20; ++i) {
        printf("%2d: ", i + 1);
        for (j = 0; j < lcounts[i]; ++j) {
            putchar('*');
        }
        putchar('\n');
    }

    printf("\nVertical histogram:\n");

    int max;
    max = lcounts[0];
    for (i = 1; i < 20; ++i) {
        if (max < lcounts[i]) {
            max = lcounts[i];
        }
    }

    while (max > 0) {
        for (i = 0; i < 20; ++i) {
            if (lcounts[i] >= max) {
                printf("  *");
            } else {
                printf("   ");
            }
        }
        putchar('\n');
        --max;
    }

    for (i = 1; i <= 20; ++i) {
        printf("%3d", i);
    }

    putchar('\n');

    return 0;
}
