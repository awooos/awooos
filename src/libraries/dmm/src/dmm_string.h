#ifndef DMM_STRING_H
#define DMM_STRING_H

#include <stddef.h>

void *dmm_memcpy(void *dest, const void *src, size_t n);
void *dmm_memset(void *s, int c, size_t n);
void dmm_strncpy_null(char *dest, const char *src, size_t destsize);

#endif
