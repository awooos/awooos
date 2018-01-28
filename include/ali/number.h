#ifndef ALI__ALI_NUMBER_H
#define ALI__ALI_NUMBER_H

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

#endif
