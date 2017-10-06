#ifndef STDDEF_H
#define STDDEF_H

#ifdef __x86_64
    // 8 bytes.
    typedef unsigned long int size_t;
#else
    // 4 bytes.
    typedef unsigned int size_t;
#endif

#endif /* STDDEF_H */

