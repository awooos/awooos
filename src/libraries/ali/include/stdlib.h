#ifndef ALI__STDLIB_H
#define ALI__STDLIB_H

#include <ali.h>

#define malloc(size) ali_malloc(size, __FUNCTION__, __FILE__, __LINE__)
#define free(ptr) ali_free(ptr, __FUNCTION__, __FILE__, __LINE__)
#define calloc(nmemb, size) ali_calloc(nmemb, size, __FUNCTION__, __FILE__, __LINE__)
#define realloc(ptr, size) ali_realloc(ptr, size, __FUNCTION__, __FILE__, __LINE__)

int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);

long int strtol(const char *nptr, char **endptr, int base);
long long int strtoll(const char *nptr, char **endptr, int base);

#endif
