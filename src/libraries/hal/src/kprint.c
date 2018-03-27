#include <hal.h>
#include <ali/event.h>

int kprint(const char *string) {
    event_trigger("kernel print", (char*)string, 0);

    return 0;
}
