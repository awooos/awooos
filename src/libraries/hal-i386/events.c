#include <eventually.h>
#include <scheduler.h>
#include <kernel.h>

#define REGISTER_HANDLER(name, callback) \
    kprint("Adding event handler for " name ": " # callback ".\n"); \
    eventually_add_handler(name, &callback)

void hal_events_init()
{
    REGISTER_HANDLER("timer", scheduler_callback);
}
