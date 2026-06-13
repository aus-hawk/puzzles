#include <stddef.h>
typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static Header *morecore(unsigned int);

void *malloc_(unsigned int nbytes) {
    Header *p, *prevp;
    unsigned int nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { // no free list yet
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {     // big enough
            if (p->s.size == nunits) { // exactly
                prevp->s.ptr = p->s.ptr;
            } else { // allocate tail end
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) { // wrapped around free list
            if ((p = morecore(nunits)) == NULL) {
                return NULL; // none left
            }
        }
    }
}

void free(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1; // point to block header
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break; // freed block at start or end of arena
        }
    }

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

#define NALLOC 1024

static Header *morecore(unsigned int nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header)); // need to look up actual usage in :Man
    if (cp == (char *)-1) {
        return NULL;
    }
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));
    return freep;
}

void *calloc_(unsigned int n, unsigned int size) {
    void *block;

    if ((block = malloc_(n * size)) == NULL) {
        return NULL;
    }

    for (int i = 0; i < n * size; ++i) {
        ((char *)block)[i] = 0;
    }

    return block;
}
