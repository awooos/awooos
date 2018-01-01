#ifndef AWOO_LIBC_MALLOC_H
#define AWOO_LIBC_MALLOC_H

typedef void *(MallocFn)(size_t size);
typedef void (FreeFn)(void *ptr);

void memory_manager_init(MallocFn *mallocfn, FreeFn *freefn);

typedef struct malloc_header_s {
    void *data;
    size_t size;
    struct malloc_header_s *prev;
    struct malloc_header_s *next;
} MallocHeader;

typedef struct memory_manager_functions_s {
    MallocFn *malloc;
    FreeFn *free;
} MemoryManagerFunctions;

#endif
