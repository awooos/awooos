#ifndef AWOOSTR_H
#define AWOOSTR_H

#include <stddef.h>
#include <stdint.h>

size_t _decimal_places_in_uint(uint64_t n, size_t radix);

uint64_t uint64_div(uint64_t a, uint64_t b);
uint64_t uint64_mod(uint64_t a, uint64_t b);

char *uint64_to_str_radix(uint64_t n, size_t radix);
char *uint64_to_str(uint64_t n);
char *int64_to_str_radix(int64_t n, size_t radix);
char *int64_to_str(int64_t n);

#define str(x) _Generic((x),    uint8_t:  uint64_to_str((uint64_t)(x)), \
                                uint16_t: uint64_to_str((uint64_t)(x)), \
                                uint32_t: uint64_to_str((uint64_t)(x)), \
                                uint64_t: uint64_to_str((uint64_t)(x)), \
                                unsigned long: uint64_to_str((uint64_t)(x)), /* ??? */ \
                                int8_t:   int64_to_str((int64_t)(x)),  \
                                int16_t:  int64_to_str((int64_t)(x)),  \
                                int32_t:  int64_to_str((int64_t)(x)),  \
                                int64_t:  int64_to_str((int64_t)(x)),  \
                                signed long: int64_to_str((int64_t)(x))) /* ??? */

#define n_to_str_radix(n, radix) _Generic((n),  uint8_t:  uint64_to_str_radix, \
                                                uint16_t: uint64_to_str_radix, \
                                                uint32_t: uint64_to_str_radix, \
                                                uint64_t: uint64_to_str_radix, \
                                                int8_t:   int64_to_str_radix,  \
                                                int16_t:  int64_to_str_radix,  \
                                                int32_t:  int64_to_str_radix,  \
                                                int64_t:  int64_to_str_radix)(n, radix)

#endif
