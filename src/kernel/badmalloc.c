/* Technically a memory allocator. */

#include <stddef.h>

extern size_t *kernel_end;

void *badmalloc (size_t size) {
    static size_t *ptr = 0;

    if (ptr == 0) {
        ptr = kernel_end;
    }

    ptr += size;

    return (ptr - size);
}

/* Honestly, this is only here because I have OCD. -@duckinator */
void badfree(){}
