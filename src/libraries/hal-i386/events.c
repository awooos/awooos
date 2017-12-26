#include <eventually.h>
#include <scheduler.h>
#include <kernel.h>

#define REGISTER_HANDLER(name, callback) \
    kprint("Adding event handler for " name ": " # callback ".\n"); \
    eventually_event_watch(name, &callback)

void hal_events_init()
{
    REGISTER_HANDLER("IRQ 0 timer", scheduler_callback);
    REGISTER_HANDLER("HAL scheduler next", hal_scheduler_callback);
}
