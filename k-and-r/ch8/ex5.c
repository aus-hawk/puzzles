#include <stdio.h>
#include <sys/stat.h>

void dirwalk(char *, void(*fcn)(char *));

void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode &S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("size: %81ld, owner: %u, %s\n", stbuf.st_size, stbuf.st_uid, name);
}
