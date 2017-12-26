#include <dmm.h>
#include <stddef.h>
#include "nicer_allocator.h"

static Header base;
static Header *freep = NULL;

/* Maybe it would be better to allocate in more than units of pages? */
static Header *morecore(unsigned nu)
{
    Header *cp;
    Header *up;
    unsigned int tmp;

    if (nu <= NALLOC) {
        nu = NALLOC;
    } else {
        return NULL;
    }

    // first_frame() cannot fail: failures trigger panics.
    tmp = first_frame();


    cp = (void*)tmp;
    up = cp;
    up->s.size = nu;

    kfree((void *)(up+1));

    return freep;
}

void *kmalloc(unsigned int nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) +1;

    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) { /* exactly */
                prevp->s.ptr = p->s.ptr;
            } else { /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;

            return (void *)(p+1);
        }

        if ((p == freep) && (p = morecore(nunits)) == NULL) {
            break; /* none left */
        }

    }

    return NULL;
}

void kfree(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}
