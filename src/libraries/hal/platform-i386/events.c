#include <ali/event.h>
#include "exceptions.h"
#include "gdt.h"
#include "hal_keyboard.h"
#include "interrupts.h"
#include "keyboard.h"
#include "multiboot.h"

void hal_register_platform_events()
{
    event_watch("HAL init",                &hal_gdt_init);
    event_watch("HAL init",                &hal_exceptions_init);
    event_watch("HAL init",                &hal_multiboot_init);
    event_watch("HAL init",                &hal_interrupts_enable);

    event_watch("HAL interrupts enable",   &hal_interrupts_enable);
    event_watch("HAL interrupts disable",  &hal_interrupts_disable);
    event_watch("IRQ 1 keyboard",          &hal_keyboard_callback);
}
