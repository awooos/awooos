#include <ali/event.h>
#include <ali/modifiers.h>
#include <awoo.h>
#include <hal.h>

void greeter_display_greeting(UNUSED const char *event_name, UNUSED void *data,
        UNUSED size_t data_size)
{
    kprint(AWOO_INFO);

    event_trigger("HAL metadata print", NULL, 0);

    kprint("\r\n\r\n");
}

void greeter_register_events()
{
    event_watch("greeter display", greeter_display_greeting);
}
