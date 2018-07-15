#include <ali/event.h>
#include "exceptions.h"
#include "gdt.h"
#include "interrupts.h"

void hal_register_platform_events()
{
    event_watch("HAL init",                &hal_gdt_init);
    event_watch("HAL init",                &hal_exceptions_init);
    event_watch("HAL init",                &hal_interrupts_enable);

    event_watch("HAL interrupts enable",   &hal_interrupts_enable);
    event_watch("HAL interrupts disable",  &hal_interrupts_disable);
}
