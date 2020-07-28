#include "../include/ali.h"
#include <stddef.h>
#include <stdio.h>
#include <tinker.h>

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);

void add_ali_tests(void);

void *_test_malloc(size_t size, const char function[], const char filename[],
        size_t line)
{
    (void)function; (void)filename; (void)line;
    return malloc(size);
}

void _test_free(void *ptr, const char function[], const char filename[],
        size_t line)
{
    (void)function; (void)filename; (void)line;
    free(ptr);
}

void *_test_realloc(void *ptr, size_t size, const char function[],
        const char filename[], size_t line)
{
    (void)function; (void)filename; (void)line;
    return realloc(ptr, size);
}

int main(void)
{

    tinker_verbose = 1;
    ali_init(_test_malloc, _test_free, _test_realloc);

    add_ali_tests();

    if (!tinker_run_tests(&putchar)) {
        return 1;
    }

    return 0;
}
