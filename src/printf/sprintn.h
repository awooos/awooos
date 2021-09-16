#ifndef ALI_PRINTF_SPRINTN_H
#define ALI_PRINTF_SPRINTN_H

#include <stddef.h>
#include <stdint.h>

#include "vprintf.h"

enum SprintnFlags {
    SP_NONE = 0,
    SP_LEFT_JUSTIFIED,
    SP_SPACE_IF_POSITIVE,
    SP_ALT_FORM,
    SP_LEADING_ZEROS,
    SP_UPPER,
};

int ali_sprintni(char *str, size_t size, int min_length, int64_t number,
                 size_t base, VprintFlags *flags, int upper, int precision);
int ali_sprintnu(char *str, size_t size, int min_length, uint64_t number,
                 size_t base, VprintFlags *flags, int upper, int precision);

#endif
