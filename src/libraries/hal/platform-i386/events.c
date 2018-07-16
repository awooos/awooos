#include <ali/event.h>
#include "gdt.h"

void hal_register_platform_events()
{
    event_watch("HAL init",                &hal_gdt_init);
}
