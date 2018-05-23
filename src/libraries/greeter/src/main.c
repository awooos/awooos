#include <ali/event.h>
#include <ali/text.h>

void greeter_display_greeting(void *data)
{
    char **metadata = (char**)data;

    for (size_t idx = 0; metadata[idx] != NULL; idx++) {
        print(metadata[idx]);
    }

    print("\r\n\r\n");
}

__attribute__((constructor))
void greeter_register_events()
{
    event_watch("greeter display", greeter_display_greeting);
}
