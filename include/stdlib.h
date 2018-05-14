#ifndef ALI__STDLIB_H
#define ALI__STDLIB_H

#include <ali.h>

#define malloc(size) ali_malloc(size, __FUNCTION__, __FILE__, __LINE__)
#define free(ptr) ali_free(ptr, __FUNCTION__, __FILE__, __LINE__)
#define calloc(nmemb, size) ali_calloc(nmemb, size, __FUNCTION__, __FILE__, __LINE__)
#define realloc(ptr, size) ali_realloc(ptr, size, __FUNCTION__, __FILE__, __LINE__)

#endif
