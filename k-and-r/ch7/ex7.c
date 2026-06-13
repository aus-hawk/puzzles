#include <stdio.h>
#include <string.h>

int search(FILE *fp, char *pat, int except, int number, char *name);

int main(int argc, char *argv[]) {
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                return -1;
            }
        }
    }

    char *pattern = *argv++;
    if (argc == 1) {
        found = search(stdin, pattern, except, number, "stdin");
    } else {
        while (--argc > 0) {
            FILE *fp = fopen(*argv, "r");
            found += search(fp, pattern, except, number, *argv++);
        }
    }

    return found;
}

int fgetl(FILE *fp, char *line, int max) {
    if (fgets(line, max, fp) == NULL) {
        return 0;
    } else {
        return strlen(line);
    }
}

#define MAXLINE 1000

int search(FILE *fp, char *pat, int except, int number, char *name) {
    long lineno = 0;
    int found = 0;
    char line[MAXLINE];
    while (fgetl(fp, line, MAXLINE) > 0) {
        lineno++;
        if ((strstr(line, pat) != NULL) != except) {
            printf("%s:", name);
            if (number) {
                printf("%ld:", lineno);
            }
            printf(" %s", line);
            found++;
        }
    }
    return found;
}
