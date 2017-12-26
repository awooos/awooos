#ifndef STRING_H
#define STRING_H

#include <stddef.h>

extern void *memmove_tmp(void *dest, const char *src, size_t n, void *tmp);
//extern void *memmove(void *dest, const char *src, size_t n);
extern void *memset(void *s, int c, size_t n);

extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, size_t n);

// extern char *strcat(char *dest, const char *src);
// extern char *strncat(char *dest, const char *src, size_t n);

extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t n);

// extern char *strchr(const char *s, int c);
// extern char *strrchr(const char *s, int c);

extern size_t strlen(const char *str);

char *strrev(char *str);

#endif
