#include <scheduler.h>
#include <stddef.h>
#include <awoo/modifiers.h>

MAY_PANIC void hal_scheduler_callback(const char *event_name, void *_state)
{
    SchedulerState *state = (SchedulerState*)_state;
    // ...
}
