#include <ali.h>
#include <ali/event.h>
#include <ali/number.h>
#include <stdlib.h>
#include <string.h>

char *print(const char *string)
{
    event_trigger("print string", (char*)string);

    return (char*)string;
}

char *println(const char *string){
    size_t length = strlen(string);
    char *new_string = malloc(length + 2);
    strncpy(new_string, string, length);
    new_string[length] = '\n';
    new_string[length + 1] = '\0';

    print(new_string);
    free(new_string);

    return (char*)string;
}
