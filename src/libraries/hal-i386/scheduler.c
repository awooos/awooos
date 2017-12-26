#include <scheduler.h>
#include <stddef.h>
#include <awoo/modifiers.h>

MAY_PANIC void hal_scheduler_process_next(const char *event_name, void *_state)
{
    SchedulerState *state = (SchedulerState*)_state;
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
