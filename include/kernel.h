#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <awoo/modifiers.h>

#define MULTIBOOT_MAGIC 0x2BADB002

void hal_init();
void hal_shutdown();
void hal_hard_shutdown();
void hal_test_fail_shutdown();
void kprint(const char *string);

#endif
