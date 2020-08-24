#ifndef FLAIL_PLATFORM_H
#define FLAIL_PLATFORM_H

#include <stddef.h>

void flail_stack_dump_with_stack(size_t *stack_start, size_t *_stack_end);
void flail_stack_dump(void);

void flail_wait_forever(void);

#endif
