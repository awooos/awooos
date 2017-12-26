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

typedef struct process_reference_s {
    size_t id;
} ProcessReference;

typedef struct scheduler_state_s {
    Process processes[MAX_PROCESSES];
    size_t current_process;
    size_t number_of_processes;
    void *data;
} SchedulerState;

MAY_PANIC void scheduler_process_next(const char *event_name, void *data);
MAY_PANIC void scheduler_process_start(const char *event_name, void *data);
MAY_PANIC void scheduler_process_stop(const char *event_name, void *data);


MAY_PANIC void hal_scheduler_process_next(const char *event_name, void *_state);
MAY_PANIC void hal_scheduler_process_start(const char *event_name, void *_state);
MAY_PANIC void hal_scheduler_process_stop(const char *event_name, void *_state);

#endif
