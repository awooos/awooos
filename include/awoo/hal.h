#ifndef AWOO_HAL_H
#define AWOO_HAL_H

#include <awoo/modifiers.h>
#include <stddef.h>

// Used for event handlers.

void hal_shutdown_hard(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length);

void hal_shutdown_test_fail(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length);

#endif
