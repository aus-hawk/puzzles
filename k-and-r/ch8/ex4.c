#include <stdlib.h>

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;    // characters left
    char *ptr;  // next character position
    char *base; // location of buffer
    int flag;   // mode of file access
    int fd;     // file descriptor
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
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
        if ((fp->flag & (_READ | _WRITE)) == 0) {
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
        return EOF;
    }
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = malloc(bufsize)) == NULL) {
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= EOF;
        } else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c, FILE *fp) {
    if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
        return EOF;
    }
    if (fp->flag & _UNBUF) {
        if (write(fp->fd, &c, 1) == -1) {
            fp->flag |= _ERR;
            return EOF;
        } else {
            fp->cnt = 0;
            return c;
        }
    }
    if (fp->base == NULL) {
        if ((fp->base = malloc(BUFSIZ)) == NULL) {
            return EOF;
        }
    } else if (write(fp->fd, fp->base, BUFSIZ) == -1) {
        fp->flag |= _ERR;
        return EOF;
    }
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ;
    *fp->ptr++ = c;
    fp->cnt--;
    return c;
}

int fflush(FILE *fp) {
    if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
        return EOF;
    }
    if (fp->base == NULL) {
        return 0;
    }
    if (write(fp->fd, fp->base, fp->ptr - fp->base) == -1) {
        fp->flag |= _ERR;
        return EOF;
    }
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ;
    return 0;
}

int fclose(FILE *fp) {
    if (close(fp->fd) == -1) {
        fp->flag |= _ERR;
        return EOF;
    }
    if (fp->base != NULL) {
        free(fp->base);
    }
    fp->base = NULL;
    fp->flag = 0;
    return 0;
}

int fseek(FILE *fp, long offset, int origin) {
    lseek(fp->fd, offset, origin);
    if (fp->flag & _UNBUF) {
        return 0;
    }
    if (fp->flag & _WRITE) {
        return (fflush(fp) == EOF) ? -1 : 0;
    }
    return (_fillbuf(fp) == EOF) ? -1 : 0;
}
