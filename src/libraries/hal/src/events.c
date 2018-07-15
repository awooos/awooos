#include <ali/event.h>
#include <hal.h>
#include <dmm.h>
#include "hal_flail.h"
#include "panic.h"

__attribute__((constructor))
void hal_register_events()
{
    event_watch("HAL init",                &hal_flail_init);
    hal_register_platform_events();
    event_watch("register panic function", (void (*)(void*))hal_panic_init);
    event_watch("register panic function", (void (*)(void*))dmm_init);
}
