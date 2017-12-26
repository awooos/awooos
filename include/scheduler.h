#ifndef AWOO_SCHEDULER_H
#define AWOO_SCHEDULER_H

#include <awoo/modifiers.h>
#include <stdbool.h>

typedef struct process_s {
    size_t id;
    uint8_t used;
} Process;

MAY_PANIC void scheduler_callback();

#endif
