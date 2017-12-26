#include <scheduler.h>
#include <awoo/modifiers.h>
#include "exceptions.h"

#define SCHEDULER_MAX_TICKS_PER_TURN 20

MAY_PANIC void hal_scheduler_process_next(const char *event_name, void *_state)
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
}

MAY_PANIC void hal_scheduler_process_start(const char *event_name,
        void *_state)
{
    SchedulerState *state = (SchedulerState*)_state;
    // ...
}

MAY_PANIC void hal_scheduler_process_stop(const char *event_name,
        void *_state)
{
    SchedulerState *state = (SchedulerState*)_state;
    // ...
}
