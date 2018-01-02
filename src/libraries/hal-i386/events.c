#include <eventually.h>
#include <scheduler.h>
#include <awoo/hal.h>
#include <kernel.h>

#define REGISTER_HANDLER(name, callback) \
    kprint("Adding event handler for " name ": " # callback ".\n"); \
    eventually_event_watch(name, &callback)

void hal_events_init()
{
    REGISTER_HANDLER("IRQ 0 timer",             scheduler_process_next);
    REGISTER_HANDLER("scheduler process start", scheduler_process_start);
    REGISTER_HANDLER("scheduler process stop",  scheduler_process_stop);

    REGISTER_HANDLER("HAL scheduler process next",  hal_scheduler_process_next);
    REGISTER_HANDLER("HAL scheduler process start", hal_scheduler_process_start);
    REGISTER_HANDLER("HAL scheduler process stop",  hal_scheduler_process_stop);

    REGISTER_HANDLER("HAL interrupts enable",   hal_enable_interrupts);
    REGISTER_HANDLER("HAL interrupts disable",  hal_disable_interrupts);

    kprint("\r\n");
}
