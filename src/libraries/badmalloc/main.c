/* Technically a memory allocator. */

#include <stddef.h>
#include <badmalloc.h>

static size_t *ptr;

void badmalloc_init(size_t *kernel_end_)
{
    ptr = kernel_end_ + 1;
}

void *badmalloc(size_t size) {
    ptr += size;

    return ptr - size;
}
