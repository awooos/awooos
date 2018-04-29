#include <ali/event.h>
#include <ali/modifiers.h>
#include <ali/text.h>
#include <awoo.h>

void greeter_display_greeting(UNUSED const char *event_name, UNUSED void *data,
        UNUSED size_t data_size)
{
    print(AWOO_INFO);

    event_trigger("HAL metadata print", NULL, 0);

    print("\r\n\r\n");
}

void greeter_register_events()
{
    event_watch("greeter display", greeter_display_greeting);
}
