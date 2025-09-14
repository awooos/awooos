#ifndef TGMATH_H
#define TGMATH_H

#define abs(n) _Generic((n),    int32_t: abs(n), \
                                int16_t: abs(n), \
                                int8_t:  abs(n), \
                                double: fabs(n), \
                                float:  fabs(n))

#endif
