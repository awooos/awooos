#include <ali/event.h>
#include "basic_display.h"
#include "basic_uart.h"
#include <dmm.h>
#include "exceptions.h"
#include "gdt.h"
#include "hal_flail.h"
#include "hal_init.h"
#include "hal_keyboard.h"
#include "idt.h"
#include "interrupts.h"
#include "keyboard.h"
#include "multiboot.h"
#include "panic.h"
#include "shutdown.h"

void hal_register_events()
{
    event_watch("HAL init",                &hal_basic_display_init);
    event_watch("HAL init",                &hal_basic_uart_init);
    event_watch("HAL init",                &hal_gdt_init);
    event_watch("HAL init",                &hal_idt_init);
    event_watch("HAL init",                &hal_exceptions_init);
    event_watch("HAL init",                &hal_flail_init);
    event_watch("HAL init",                &hal_multiboot_init);
    event_watch("HAL init",                &hal_init);
    event_watch("HAL init",                &hal_interrupts_enable);

    event_watch("HAL shutdown",            &hal_shutdown);
    event_watch("HAL shutdown test fail",  &hal_shutdown_test_fail);
    event_watch("HAL interrupts enable",   &hal_interrupts_enable);
    event_watch("HAL interrupts disable",  &hal_interrupts_disable);
    event_watch("IRQ 1 keyboard",          &hal_keyboard_callback);

    event_watch("register panic function", (void (*)(void*))hal_panic_init);
    event_watch("register panic function", (void (*)(void*))dmm_init);

    event_watch("print string",            (void (*)(void*))&hal_basic_display_print);
    event_watch("print string",            (void (*)(void*))&hal_basic_uart_print);
}
