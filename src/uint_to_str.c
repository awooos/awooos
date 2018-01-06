#include <stddef.h>
#include "uint_to_str.h"

// ASSUMPTION: number will never be larger than can fit in a uint64_t.
//
// NOTE: If the buffer is too small, the string gets truncated.
// NOTE: This is inefficient as hell but I don't care because at the point it's
//          called everything is already fucked.
char *flail_uint_to_str(char buffer[UINT64_CHARS_WITH_NULL],
        size_t n, size_t radix)
{
    unsigned char value;
    size_t tmp = n;

    // Set the entire buffer to NULL bytes.
    // (Inlined memset() to avoid dependencies.)
    for (size_t idx = 0; idx < UINT64_CHARS_WITH_NULL; idx++) {
        buffer[idx] = 0;
    }

    // Loop through the digits and add them in reverse order,
    // starting at the end of the string and working back.
    size_t idx;
    for (idx = UINT64_DIGITS; idx > 0; idx--) {
        buffer[idx - 1] = "0123456789abcdef"[tmp % radix];
        tmp /= radix;
    }

    return buffer;
}
