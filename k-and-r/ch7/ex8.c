#include <stdio.h>
#include <string.h>

int fgetl(FILE *fp, char *line, int max) {
    if (fgets(line, max, fp) == NULL) {
        return 0;
    } else {
        return strlen(line);
    }
}

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    while (*++argv != NULL) {
        printf("/* File: %s */\n", *argv);
        FILE *fp = fopen(*argv, "r");
        int lines = 0, pages = 0;
        while (fgetl(fp, line, MAXLINE) > 0) {
            printf("%s", line);
            if (++lines > 24) {
                printf("/* (End of page %d) */\n\f", ++pages);
                printf("/* File: %s */\n", *argv);
                lines = 0;
            }
        }
        if (lines > 0) {
            printf("/* (End of page %d) */\n\f", ++pages);
        }
    }
    printf("\n");
    return 0;
}
