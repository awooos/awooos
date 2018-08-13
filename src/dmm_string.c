#include "dmm_string.h"
#include <stddef.h>

void *_dmm_memcpy(void *dest, const void *src, size_t n)
{
    char *dest_ = (char*)dest;
    char *src_ = (char*)src;

    for (size_t i = 0; i < n; i++) {
        dest_[i] = src_[i];
    }

    return dest;
}

void *_dmm_memset(void *s, int c, size_t n)
{
    char *s_ = (char*)s;
    for (size_t i = 0; i < n; i++) {
        s_[i] = (char)c;
    }

    return s;
}

// Similar to strncpy(), except it sets the remaining bytes to null.
void _dmm_strncpy_null(char *dest, const char *src, size_t destsize)
{
    size_t srcsize = 0;
    size_t min;

    for (size_t i = 0; src[i]; i++) {
        srcsize = i;
    }

    min = (srcsize < destsize) ? srcsize : destsize;

    // Initialize destination buffer to null bytes.
    _dmm_memset(dest, 0, destsize);
    // Copy src buffer to destination buffer.
    _dmm_memcpy(dest, src, min);
    // Terminate with a null byte.
    dest[destsize - 1] = 0;
}
