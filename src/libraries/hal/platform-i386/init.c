#include <awoo.h>
#include <ali.h>
#include <dmm.h>
#include <hal.h>
#include <stddef.h>

#include "exceptions.h"
#include "idt.h"
#include "multiboot.h"

void hal_basic_display_print(const char *string);
void hal_basic_uart_print(const char *string);

extern char kernel_comment_start;

void hal_print(const char *string) {
    hal_basic_uart_print(string);
    hal_basic_display_print(string);
}

void hal_init(void) {
    hal_exceptions_init();
    hal_idt_init();
    hal_multiboot_init();

    ali_init(&dmm_malloc_, &dmm_free_, &dmm_realloc_);


    hal_print(AWOO_INFO);
    hal_print("\r\n");
    hal_print("Compiled with: ");
    hal_print(&kernel_comment_start);
    hal_print("\r\n");

    hal_interrupts_disable();
}
