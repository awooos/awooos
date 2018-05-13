#ifndef FLAIL_UINT_TO_STR_H
#define FLAIL_UINT_TO_STR_H

#include <stddef.h>

// MAGIC NUMBER: max digits in uint64_t + 1 for a NULL byte.
#define UINT64_BUFSIZE 21

char *flail_uint_to_str(char buffer[UINT64_BUFSIZE],
        size_t n, size_t radix)

#endif
