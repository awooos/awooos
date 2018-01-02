#ifndef AWOO_HAL_H
#define AWOO_HAL_H

#include <stddef.h>

// Needed by greeter.
char *hal_compiler_information();

// Needed by ???.
size_t hal_end_memory();

// Needed by libpanic.
void hal_enable_interrupts();
void hal_disable_interrupts();

void hal_hard_shutdown();

#endif
