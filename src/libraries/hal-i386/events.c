#include <eventually.h>
#include <scheduler.h>
#include <kernel.h>
#include "shutdown.h"
#include "interrupts.h"
#include "hal_init.h"
#include "text.h"
#include "metadata.h"

#define REGISTER_HANDLER(name, callback) \
    eventually_event_watch(name, &callback)

void hal_register_events()
{
    REGISTER_HANDLER("kernel print", hal_print_callback);

    REGISTER_HANDLER("HAL init", hal_init);

    REGISTER_HANDLER("HAL metadata print", hal_metadata_print);


    REGISTER_HANDLER("HAL interrupts enable",   hal_enable_interrupts);
    REGISTER_HANDLER("HAL interrupts disable",  hal_disable_interrupts);

    REGISTER_HANDLER("HAL shutdown hard",       hal_shutdown_hard);
    REGISTER_HANDLER("HAL shutdown test fail",       hal_shutdown_test_fail);

    REGISTER_HANDLER("IRQ 0 timer",             scheduler_process_next);
    REGISTER_HANDLER("scheduler process start", scheduler_process_start);
    REGISTER_HANDLER("scheduler process stop",  scheduler_process_stop);

    REGISTER_HANDLER("HAL scheduler process next",  hal_scheduler_process_next);
    REGISTER_HANDLER("HAL scheduler process start", hal_scheduler_process_start);
    REGISTER_HANDLER("HAL scheduler process stop",  hal_scheduler_process_stop);
}
