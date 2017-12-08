/* Technically a memory allocator. */

#include <stddef.h>
#include <badmalloc.h>

static size_t *badmalloc_kernel_end;

void badmalloc_init(size_t *kernel_end_)
{
    badmalloc_kernel_end = kernel_end_;
}

void *badmalloc(size_t size) {
    static size_t *ptr = NULL;

    if (ptr == NULL) {
        ptr = badmalloc_kernel_end;
    }

    ptr += size;

    return (size_t*)(&ptr - size);
}
