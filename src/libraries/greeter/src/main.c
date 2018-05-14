#include <ali/event.h>
#include <ali/modifiers.h>
#include <ali/text.h>
#include <awoo.h>

void greeter_display_greeting(UNUSED void *data)
{
    print(AWOO_INFO);

    event_trigger("HAL metadata print", NULL);

    print("\r\n\r\n");
}

void greeter_register_events()
{
    event_watch("greeter display", greeter_display_greeting);
}
