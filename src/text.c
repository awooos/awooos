#include <ali.h>
#include <ali/event.h>

int print(const char *string)
{
    event_trigger("print string", (char*)string, 0);

    return 0;
}

int println(const char *string)
{
    size_t length = strlen(string);
    char *new_string = ali_malloc(length + 2);
    strncpy(new_string, string, length);
    new_string[length] = '\n';
    new_string[length + 1] = '\0';

    return print(new_string);
}
