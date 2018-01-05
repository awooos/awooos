#include <ali.h>

static AliMemoryManagerFunctions mmfns;

void ali_init(AliMallocFn *mallocfn, AliFreeFn *freefn,
        AliReallocFn *reallocfn, AliCallocFn *callocfn)
{
    mmfns.malloc = mallocfn;
    mmfns.free = freefn;
    mmfns.realloc = reallocfn;
    mmfns.calloc = callocfn;
}

void *ali_malloc(size_t size)
{
    return mmfns.malloc(size);
}

void alifree(void *ptr)
{
    mmfns.free(ptr);
}

void *ali_calloc(size_t nmemb, size_t size)
{
    return mmfns.calloc(nmemb, size);
}

void *ali_realloc(void *ptr, size_t size)
{
    return mmfns.realloc(ptr, size);
}

