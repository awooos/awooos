#ifndef ALI_PRINTF_SPRINTN_H
#define ALI_PRINTF_SPRINTN_H

#include <stddef.h>
#include <stdint.h>

int ali_sprintni(char *str, size_t size, int min_length,
                 int64_t number, size_t base, int flags, int precision);
int ali_sprintnu(char *str, size_t size, int min_length,
                 uint64_t number, size_t base, int flags, int precision);

#endif
