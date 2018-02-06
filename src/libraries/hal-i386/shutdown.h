#ifndef HAL_SHUTDOWN_H
#define HAL_SHUTDOWN_H

#include <awoo/modifiers.h>

void hal_shutdown_hard(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length);

void hal_shutdown_test_fail(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length);

#endif
