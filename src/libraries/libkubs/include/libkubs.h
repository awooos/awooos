#ifndef LIBKUBS_H
#define LIBKUBS_H

#include <stddef.h>

typedef void (Kubs_PanicFn)(const char *message, const char *function,
        const char *filename, size_t line);

void kubs_init(Kubs_PanicFn *panicfn_);

#endif
