#ifndef DUX_DMM_H
#define DUX_DMM_H

#include <stddef.h>

void dmm_init(size_t _kernel_end, size_t _end_memory);
void *kmalloc(size_t nbytes);
void kfree(void *ap);

#endif
