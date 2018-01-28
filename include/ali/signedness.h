#ifndef ALI__ALI_SIGNEDNESS_H
#define ALI__ALI_SIGNEDNESS_H

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

#define is_unsigned(n) ((is_signed(n) == 1) ? 0 : 1)

#endif
