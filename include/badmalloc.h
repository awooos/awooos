#ifndef BADMALLOC_H
#define BADMALLOC_H

#include <stddef.h>

extern void badmalloc_init(size_t *kernel_end_);
extern void *badmalloc(size_t size);

#endif /* BADMALLOC_H */
