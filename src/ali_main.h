#ifndef ALI_MAIN_H
#define ALI_MAIN_H

#include <stddef.h>

void *ali_malloc(size_t size);
void ali_free(void *ptr);
void *ali_calloc(size_t nmemb, size_t size);
void *ali_realloc(void *ptr, size_t size);

#endif
