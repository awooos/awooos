#include <ali.h>
#include <string.h>

static AliMemoryManagerFunctions mmfns;

void ali_init(AliMallocFn *mallocfn, AliFreeFn *freefn,
        AliReallocFn *reallocfn)
{
    mmfns.malloc = mallocfn;
    mmfns.free = freefn;
    mmfns.realloc = reallocfn;
}

void *ali_malloc(size_t size, const char function[],
        const char filename[], size_t line)
{
    return mmfns.malloc(size, function, filename, line);
}

void ali_free(void *ptr, const char function[],
        const char filename[], size_t line)
{
    mmfns.free(ptr, function, filename, line);
}

void *ali_calloc(size_t nmemb, size_t size, const char function[],
        const char filename[], size_t line)
{
    size_t total_size = nmemb * size;
    void *buffer = mmfns.malloc(total_size);

    memset(buffer, 0, total_size);

    return buffer;
}

void *ali_realloc(void *ptr, size_t size, const char function[],
        const char filename[], size_t line)
{
    return mmfns.malloc(size, function, filename, line);
}
