#include <ali/text.h>
#include <ali/event.h>

// TODO: Remove print().
char *print(const char *string)
{
    event_trigger("print string", (char*)string);

    return (char*)string;
}
