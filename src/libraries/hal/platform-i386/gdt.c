#include <ali/event.h>
#include "gdt.h"

__attribute__((constructor))
void hal_gdt_register_events()
{
    event_watch("HAL gdt init", &hal_gdt_init);
}
