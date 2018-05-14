#include <ali/event.h>
#include "hal_init.h"
#include "hal_keyboard.h"
#include "interrupts.h"
#include "keyboard.h"
#include "metadata.h"
#include "shutdown.h"
#include "text.h"

#define REGISTER_HANDLER(name, callback) \
    event_watch(name, &callback)

void hal_register_events()
{
    REGISTER_HANDLER("print string",            hal_print_callback);
    REGISTER_HANDLER("HAL init",                hal_init);
    REGISTER_HANDLER("HAL shutdown",            hal_shutdown);
    REGISTER_HANDLER("HAL shutdown test fail",  hal_shutdown_test_fail);
    REGISTER_HANDLER("HAL interrupts enable",   hal_interrupts_enable);
    REGISTER_HANDLER("HAL interrupts disable",  hal_interrupts_disable);
    REGISTER_HANDLER("IRQ 1 keyboard",          hal_keyboard_callback);
}
