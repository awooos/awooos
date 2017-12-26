#ifndef AWOO_SCHEDULER_H
#define AWOO_SCHEDULER_H

#include <awoo/modifiers.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MAX_PROCESSES 2048

typedef struct process_s {
    size_t id;
    uint8_t used;
} Process;

typedef struct scheduler_state_s {
    Process processes[MAX_PROCESSES];
    size_t current_process;
    size_t number_of_processes;
} SchedulerState;

MAY_PANIC void scheduler_callback();

MAY_PANIC void hal_scheduler_callback(const char *event_name, void *_state);

#endif
