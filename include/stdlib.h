#ifndef STDLIB_H
#define STDLIB_H

#include <ali.h>

#define malloc(size) ali_malloc(size)
#define free(ptr) ali_free(ptr)
#define calloc(nmemb, size) ali_calloc(nmemb, size)
#define realloc(ptr, size) ali_realloc(ptr, size)

#endif
