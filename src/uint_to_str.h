#ifndef FLAIL_UINT_TO_STR_H
#define FLAIL_UINT_TO_STR_H

#include <stddef.h>

// MAGIC NUMBER: max digits in uint64_t.
#define UINT64_DIGITS 20
// MAGIC NUMBER: number of digits in a uitn64_t, plus one to include a null byte.
#define UINT64_CHARS_WITH_NULL (UINT64_DIGITS + 1)

char *flail_uint_to_str(char buffer[UINT64_CHARS_WITH_NULL],
        size_t n, size_t radix);

#endif
