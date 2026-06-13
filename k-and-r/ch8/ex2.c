#include <stdlib.h>

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt; // characters left
    char *ptr; // next character position
    char *base; // location of buffer
    unsigned int read : 1;
    unsigned int write : 1;
    unsigned int unbuf : 1;
    unsigned int eof : 1;
    unsigned int err : 1;
    int fd; // file descriptor
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <unistd.h>

#define PERMS 0666

FILE *fopen_(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        /* if ((fp->flag & (_READ | _WRITE)) == 0) { */
        if (!fp->read && !fp->write) {
            break;
        }
    }
    if (fp >= _iob + OPEN_MAX) {
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY);
    }
    if (fd == -1) {
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    /* fp->flag = (*mode == 'r') ? _READ : _WRITE; */
    fp->read = fp->write = fp->unbuf = fp->eof = fp->err = 0;
    if (*mode == 'r') {
        fp->read = 1;
    } else {
        fp->write = 1;
    }
    return fp;
}

int _fillbuf(FILE *fp) {
    int bufsize;

    /* if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) { */
    if (!fp->read || fp->eof || fp->err) {
        return EOF;
    }
    /* bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; */
    bufsize = fp->unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = malloc(bufsize)) == NULL) {
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            /* fp->flag |= EOF; */
            fp->eof = 1;
        } else {
            /* fp->flag |= _ERR; */
            fp->err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int main(void) {
    FILE *fp = fopen_("stdio.txt", "r");
    int c;
    while ((c = getc(fp)) != EOF) {
        putchar(c);
    }
    return 0;
}
