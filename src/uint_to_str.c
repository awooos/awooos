#include <stddef.h>
#include "uint_to_str.h"

// ASSUMPTION: number will never be larger than can fit in a uint64_t.
// NOTE: If the buffer is too small, the string gets truncated.
char *flail_uint_to_str(char buffer[UINT64_BUFSIZE],
        size_t n, size_t radix)
{
    // Set the entire buffer to NULL bytes.
    // (Inlined memset() to avoid dependencies.)
    for (size_t idx = 0; idx < UINT64_BUFSIZE; idx++) {
        buffer[idx] = 0;
    }

    // Loop through the digits and add them in reverse order,
    // starting at the end of the string and working back.
    for (size_t idx = UINT64_BUFSIZE - 1; idx > 0; idx--) {
        buffer[idx - 1] = "0123456789abcdef"[n % radix];
        n /= radix;
    }

    return buffer;
}
