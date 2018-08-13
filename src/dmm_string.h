#ifndef DMM_STRING_H
#define DMM_STRING_H

#include <stddef.h>

void *_dmm_memcpy(void *dest, const void *src, size_t n);
void *_dmm_memset(void *s, int c, size_t n);
void _dmm_strncpy_null(char *dest, const char *src, size_t destsize);

#endif
