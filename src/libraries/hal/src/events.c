#include <ali/event.h>
#include <kernel.h>
#include "shutdown.h"
#include "interrupts.h"
#include "hal_init.h"
#include "text.h"
#include "metadata.h"

#define REGISTER_HANDLER(name, callback) \
    event_watch(name, &callback)

void hal_register_events()
{
    REGISTER_HANDLER("kernel print", hal_print_callback);

    REGISTER_HANDLER("HAL init", hal_init);

    REGISTER_HANDLER("HAL metadata print", hal_metadata_print);


    REGISTER_HANDLER("HAL interrupts enable",   hal_enable_interrupts);
    REGISTER_HANDLER("HAL interrupts disable",  hal_disable_interrupts);

    REGISTER_HANDLER("HAL shutdown",            hal_shutdown);
    REGISTER_HANDLER("HAL shutdown hard",       hal_shutdown_hard);
    REGISTER_HANDLER("HAL shutdown test fail",  hal_shutdown_test_fail);

    //REGISTER_HANDLER("IRQ 0 timer",             scheduler_process_next);
}
