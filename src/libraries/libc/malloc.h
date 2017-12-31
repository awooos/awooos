#ifndef AWOO_LIBC_MALLOC_H
#define AWOO_LIBC_MALLOC_H

typedef void *(MallocFn)(size_t size);
typedef void (FreeFn)(void *ptr);
typedef void *(CallocFn)(size_t nm, size_t size);
typedef void *(ReallocFn)(void *ptr, size_t size);

void memory_manager_init(MallocFn *mallocfn, FreeFn *freefn);

typedef struct memory_manager_functions_s {
    MallocFn *malloc;
    FreeFn *free;
//    CallocFn *calloc;
//    ReallocFn *realloc;
} MemoryManagerFunctions;

#endif
