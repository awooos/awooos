#ifndef DMM_H
#define DMM_H

#include <stddef.h>

void add_dmm_tests();
void dmm_init();

void dmm_add_memory_region(void *start, size_t length);

void *dmm_malloc(size_t size);
void dmm_free(void *ptr);
void *dmm_realloc(void *ptr, size_t size);

#ifdef DMM_INTRUSIVE
#define malloc(size) dmm_malloc(size)
#define free(ptr) dmm_free(ptr)
#define calloc(nmemb, size) dmm_calloc(nmemb, size)
#define realloc(ptr, size) dmm_realloc(ptr, size)
#endif

#endif
