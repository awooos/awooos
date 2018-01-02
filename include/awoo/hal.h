#ifndef AWOO_HAL_H
#define AWOO_HAL_H

#include <awoo/modifiers.h>
#include <stddef.h>

// Needed by greeter.
char *hal_compiler_information();

// Needed by ???.
size_t hal_end_memory();

// Needed by libpanic.
void hal_enable_interrupts();
void hal_disable_interrupts();

void hal_shutdown_hard_callback(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length);

#endif
