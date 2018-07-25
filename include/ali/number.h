#ifndef ALI__ALI_NUMBER_H
#define ALI__ALI_NUMBER_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Returns 1 if it's a number, 0 otherwise.
#define is_number(x) _Generic((x),  signed char:        1,  \
                                    signed short:       1,  \
                                    signed int:         1,  \
                                    signed long:        1,  \
                                    signed long long:   1,  \
                                    unsigned char:      1,  \
                                    unsigned short:     1,  \
                                    unsigned int:       1,  \
                                    unsigned long:      1,  \
                                    unsigned long long: 1,  \
                                    default: 0)

// Returns:
// * 1 for signed integer types.
// * 0 for unsigned integer types.
// * [unhappy compiler noises] for everything else.
#define is_signed(n) _Generic((n),  signed char:        1,  \
                                    signed short:       1,  \
                                    signed int:         1,  \
                                    signed long:        1,  \
                                    signed long long:   1,  \
                                    unsigned char:      0,  \
                                    unsigned short:     0,  \
                                    unsigned int:       0,  \
                                    unsigned long:      0,  \
                                    unsigned long long: 0)

// Returns:
// * 0 for signed integer types.
// * 1 for unsigned integer types.
// * [unhappy compiler noises] for everything else.
#define is_unsigned(n) ((is_signed(n) == 1) ? 0 : 1)

size_t decimal_places_in_uint64(uint64_t n, size_t radix);

uint64_t uint64_div(uint64_t a, uint64_t b);
uint64_t uint64_mod(uint64_t a, uint64_t b);

char *uint64_to_str_radix(uint64_t n, size_t radix);
char *int64_to_str_radix(int64_t n, size_t radix);

#define uint_to_str_radix(n, radix) uint64_to_str_radix((uint64_t)(n), radix)
#define  int_to_str_radix(n, radix)  int64_to_str_radix((int64_t)(n), radix)

#define uint_to_str(n) uint_to_str_radix((n), 10)
#define  int_to_str(n)  int_to_str_radix((n), 10)

#define n_to_str_radix(n, radix) (is_signed(n) ? int_to_str_radix(n, radix) : uint_to_str_radix(n, radix))
#define n_to_str(n) n_to_str_radix(n, 10)

// Helper functions for printing numbers!
#include <ali/text.h>

#define print_number(n) free(print(n_to_str(n)))
#define print_number_radix(n, radix) free(println(n_to_str_radix(n, radix)))
#define println_number(n) free(println(n_to_str(n)))
#define println_number_radix(n, radix) free(println(n_to_str_radix(n, radix)))

#endif
