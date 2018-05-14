#include <ali/event.h>
#include "basic_display.h"
#include "basic_uart.h"
#include <dmm.h>
#include "hal_init.h"
#include "hal_keyboard.h"
#include "interrupts.h"
#include "keyboard.h"
#include "metadata.h"
#include "panic.h"
#include "shutdown.h"
#include "text.h"

void hal_register_events()
{
    event_watch("print string",            &hal_print_callback);
    event_watch("HAL init",                &hal_init);
    event_watch("HAL shutdown",            &hal_shutdown);
    event_watch("HAL shutdown test fail",  &hal_shutdown_test_fail);
    event_watch("HAL interrupts enable",   &hal_interrupts_enable);
    event_watch("HAL interrupts disable",  &hal_interrupts_disable);
    event_watch("HAL basic I/O init",      &hal_basic_display_init);
    event_watch("HAL basic I/O init",      &hal_basic_uart_init);
    event_watch("IRQ 1 keyboard",          &hal_keyboard_callback);

    event_watch("register panic function", (void (*)(void*))hal_panic_init);
    event_watch("register panic function", (void (*)(void*))dmm_init);
}
