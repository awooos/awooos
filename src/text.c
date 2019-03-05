#include <ali/text.h>
#include <ali/event.h>

char *print(const char *string)
{
    event_trigger("print string", (char*)string);

    return (char*)string;
}

char *println(const char *string)
{
    print(string);
    print("\n");

    return (char*)string;
}
