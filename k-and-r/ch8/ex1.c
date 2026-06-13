#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    void filecopy(int, int);

    if (argc == 1) {
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                write(2, "cat: can't open ", 16);
                write(2, *argv, strlen(*argv));
                write(2, "\n", 1);
                return 1;
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    return 0;
}

void filecopy(int ifd, int ofd) {
    int buf[BUFSIZ], n;

    while ((n = read(ifd, buf, BUFSIZ)) > 0) {
        write(ofd, buf, n);
    }
}
