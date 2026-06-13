#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%s: needs two arguments\n", argv[0]);
    }
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    char line1[MAXLINE];
    char line2[MAXLINE];

    char *l1, *l2;

    do {
        l1 = fgets(line1, MAXLINE, fp1);
        l2 = fgets(line2, MAXLINE, fp2);
    } while (l1 != NULL && l2 != NULL && strcmp(line1, line2) == 0);

    if (l1 != NULL || l2 != NULL) {
        int f1_name_len = strlen(argv[1]);
        int f2_name_len = strlen(argv[2]);
        int max_name_len = f1_name_len > f2_name_len ? f1_name_len : f2_name_len;
        printf("%*s: %s", max_name_len, argv[1], (l1 == NULL) ? "EOF\n" : line1);
        printf("%*s: %s", max_name_len, argv[2], (l2 == NULL) ? "EOF\n" : line2);
    } else {
        printf("files match\n");
    }

    return 0;
}
