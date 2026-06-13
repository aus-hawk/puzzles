#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int (*modify_case)(int);
    if (strcmp(argv[0], "upper") == 0) {
        modify_case = toupper;
    } else if (strcmp(argv[0], "lower") == 0) {
        modify_case = tolower;
    } else {
        printf("Must be run as either `upper` or `lower`\n");
        return 1;
    }

    int c;
    while ((c = getchar()) != EOF) {
        putchar(modify_case(c));
    }
    return 0;
}
