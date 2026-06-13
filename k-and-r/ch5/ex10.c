#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

int main(int argc, char *argv[]) {
    double stack[STACK_SIZE];
    int sptr = 0;

    double arg1, arg2;

    while (argc-- > 1) {
        if (sptr < 0) {
            printf("bad argument format\n");
        }
        switch ((*++argv)[0]) {
        case '+':
            arg2 = stack[--sptr];
            arg1 = stack[--sptr];
            stack[sptr++] = arg1 + arg2;
            break;
        case '-':
            arg2 = stack[--sptr];
            arg1 = stack[--sptr];
            stack[sptr++] = arg1 - arg2;
            break;
        case '*':
            arg2 = stack[--sptr];
            arg1 = stack[--sptr];
            stack[sptr++] = arg1 * arg2;
            break;
        case '/':
            arg2 = stack[--sptr];
            arg1 = stack[--sptr];
            stack[sptr++] = arg1 / arg2;
            break;
        default:
            stack[sptr++] = atof(*argv);
            break;
        }
    }

    printf("%f\n", stack[0]);

    return 0;
}
