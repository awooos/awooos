/* Technically a memory allocator. */

#include <stddef.h>
#include <badmalloc.h>
#include <kernel.h>

static size_t *ptr;

void badmalloc_init()
{
    ptr = hal_badmalloc_start_address() + 1;
}

void *badmalloc(size_t size) {
    ptr += size;

    return ptr - size;
}
