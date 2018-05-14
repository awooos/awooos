#include <awoo.h>
#include <ali.h>
#include <dmm.h>
#include <ali/event.h>
#include <flail.h>
#include <hal.h>
#include "panic.h"
#include <stddef.h>
#include <stdbool.h>
#include "basic_display.h"
#include "basic_uart.h"
#include "ports.h"
#include "exceptions.h"
#include "gdt.h"
#include "idt.h"
#include "metadata.h"
#include "multiboot.h"

static bool hal_initialized = false;

void hal_init()
{
    if (hal_initialized) {
        return;
    }

    hal_basic_display_init();
    hal_basic_uart_init();
    hal_gdt_init();
    hal_idt_init();
    hal_exceptions_init();

    flail_init(AWOO_INFO, &print);
    dmm_init(&_flail_panic);

    hal_panic_init(&_flail_panic);
    hal_multiboot_init();

    ali_init(&_dmm_malloc, &_dmm_free, &_dmm_realloc);

    event_trigger("greeter display", hal_metadata());
    event_trigger("HAL interrupts enable", NULL);

    hal_initialized = true;
}
