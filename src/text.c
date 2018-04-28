#include <ali.h>
#include <ali/event.h>

void print(const char *string)
{
    event_trigger("print string", (char*)string, 0);
}

void println(const char *string)
{
    size_t length = strlen(string);
    char *new_string = ali_malloc(length + 2);
    strncpy(new_string, string, length);
    new_string[length] = '\n';
    new_string[length + 1] = '\0';

    event_trigger("print string", (char*)new_string, 0);
}
