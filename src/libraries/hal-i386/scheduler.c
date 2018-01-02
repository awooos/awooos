#include <stdlib.h>
#include <awoo/modifiers.h>
#include <scheduler.h>
#include "hal_scheduler.h"
#include "exceptions.h"

#define SCHEDULER_MAX_TICKS_PER_TURN 20

MAY_PANIC void hal_scheduler_process_next(UNUSED const char *event_name,
        void *_state, size_t data_size)
{
    SchedulerState *state = (SchedulerState*)_state;

    Process *current = &(state->processes[state->current_process]);
    Registers *regs = (Registers*)&(current->data);

    Process *next = &(state->processes[state->current_process + 1]);

    // Let it run some more.
    if (current->ticks < SCHEDULER_MAX_TICKS_PER_TURN) {
        current->ticks++;
        return;
    }

    // ...

    free(state);
}

MAY_PANIC void hal_scheduler_process_start(UNUSED const char *event_name,
        void *_state, size_t data_size)
{
    SchedulerState *state = (SchedulerState*)_state;
    // ...

    free(state);
}

MAY_PANIC void hal_scheduler_process_stop(UNUSED const char *event_name,
        void *_state, size_t data_size)
{
    SchedulerState *state = (SchedulerState*)_state;
    // ...

    free(state);
}
