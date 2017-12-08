#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <awoo/modifiers.h>

void hal_init();
void hal_shutdown();
void hal_hard_shutdown();
void hal_test_fail_shutdown();
size_t *hal_badmalloc_start_address();
void kprint(const char *string);

#endif
