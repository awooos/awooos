#include <awoo/modifiers.h>
#include <awoo/hal.h>
#include <awoo.h>
#include <kernel.h>
#include <eventually.h>

void greeter_display_greeting(UNUSED const char *event_name, UNUSED void *data,
        UNUSED size_t data_size)
{
    kprint(AWOO_INFO "\r\n");

    kprint("Compiled with ");
    kprint(hal_compiler_information());
    kprint("\r\n\r\n");
}

void greeter_register_events()
{
    eventually_event_watch("greeter display", greeter_display_greeting);
}
