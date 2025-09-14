#include <ali.h>
#include <ali/modifiers.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ali_number_print(const char *string)
{
    fputs(string, stdout);

    return (char*)string;
}

char *ali_number_println(const char *string)
{
    puts(string);

    return (char*)string;
}

// YOLO
NEEDS_IMPROVEMENT uint64_t uint64_div(uint64_t a, uint64_t b)
{
    uint64_t tmp = 0;

    if (a < b) {
        return 0;
    }

    while (a >= b) {
        a -= b;
        tmp += 1;
    }

    return tmp;
}

// YOLO × 2
NEEDS_IMPROVEMENT uint64_t uint64_mod(uint64_t a, uint64_t b)
{
    while (a >= b) {
        a -= b;
    }
    return a;
}

size_t decimal_places_in_uint64(uint64_t n, size_t radix)
{
    size_t decimal_places = 0;
    uint64_t tmp = n;

    while (tmp >= 1) {
        decimal_places += 1;
        tmp = uint64_div(tmp, radix);
    }

    if (decimal_places == 0) {
        decimal_places = 1;
    }

    return decimal_places;
}

// Converts a +uint64_t+ to a string, using the base specified in +radix+.
//
// ASSUMPTION: radix <= 36.
char *uint64_to_str_radix(uint64_t n, size_t radix)
{
    char *result;
    uint64_t tmp = n;

    size_t decimal_places = decimal_places_in_uint64((uint64_t)(n), radix);

    // Separate memory size declaration as we need to allocate enough memory
    // to store the NULL byte at the end of the string.
    size_t memory_size = decimal_places + 1;

    result = (char*)malloc(memory_size);
    memset(result, 0, memory_size);

    for (size_t idx = 0; idx < decimal_places; idx++) {
        uint8_t value = (uint8_t)uint64_mod(tmp, radix);
        result[idx] = "0123456789abcdefghijklmnopqrstuvwxyz"[value];
        tmp = uint64_div(tmp, radix);
    }

    result[decimal_places] = 0;

    return strrev(result);
}

// Converts an integer to a string, in the base specified by +radix+.
char *int64_to_str_radix(int64_t n, size_t radix)
{
    char *result;

    bool is_negative = false;
    if (n < 0) {
        is_negative = true;
        n = -n;
    }

    result = uint64_to_str_radix((uint64_t)n, radix);

    if (is_negative) {
        size_t length = strlen(result);
        char *tmp = malloc(length + 1 /* negative sign */ + 1 /* NULL */);

        tmp[0] = '-';
        strncpy((tmp + 1), result, length);

        free(result);
        return tmp;
    }

    return result;
}
