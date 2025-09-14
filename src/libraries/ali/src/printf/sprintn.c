#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ali/number.h>

#include "sprintn.h"
#include "vprintf.h"

// TODO: Move ali/number/ implementations to here.

void ali_in_place_strtoupper(char *str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        str[i] = (char)toupper(str[i]);
    }
}

int ali_sprintni(char *str, size_t size, int min_length, int64_t number,
        size_t base, VprintFlags *flags, int upper, int precision) {
    char *tmp = int64_to_str_radix(number, base);
    size_t length = strlen(tmp);

    if (length > size) {
        return -1;
    }

    (void)flags;
    (void)min_length;
    (void)precision;

    if (upper) {
        ali_in_place_strtoupper(tmp, length);
    }

    if (str) {
        strncpy(str, tmp, length);
        str[length] = 0;
    }

    free(tmp);

    return (int)length;
}

int ali_sprintnu(char *str, size_t size, int min_length, uint64_t number,
        size_t base, VprintFlags *flags, int upper, int precision) {
    char *tmp = uint64_to_str_radix(number, base);
    size_t length = strlen(tmp);

    if (length > size) {
        return -1;
    }

    (void)flags;
    (void)min_length;
    (void)precision;

    if (upper) {
        ali_in_place_strtoupper(tmp, length);
    }

    if (str) {
        strncpy(str, tmp, length);
        str[length] = 0;
    }

    return (int)length;
}
