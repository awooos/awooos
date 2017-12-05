#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>

void hal_init();
void hal_shutdown();
void hal_hard_shutdown();
void kprint(const char *string);

#endif
