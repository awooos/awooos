#include <ali.h>
#include <dmm.h>
#include <ali/event.h>
#include <ali/modifiers.h>
#include <flail.h>
#include <hal.h>
#include "panic.h"
#include <stddef.h>
#include <stdbool.h>
#include "exceptions.h"
#include "gdt.h"
#include "idt.h"
#include "metadata.h"
#include "multiboot.h"

static bool hal_initialized = false;

void hal_init(void *data)
{
    const char *kernel_info = (char*)data;

    if (hal_initialized) {
        return;
    }

    event_trigger("HAL basic I/O init", NULL);
    hal_gdt_init();
    hal_idt_init();
    hal_exceptions_init();

    flail_init(kernel_info, &print);
    dmm_init(&_flail_panic);

    hal_panic_init(&_flail_panic);
    hal_multiboot_init();

    ali_init(&_dmm_malloc, &_dmm_free, &_dmm_realloc);

    event_trigger("greeter display", hal_metadata());
    event_trigger("HAL interrupts enable", NULL);

    hal_initialized = true;
}
