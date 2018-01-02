#include <eventually.h>
#include <string.h>

void kprint(const char *string)
{
    eventually_event_trigger_immediate("kernel print", (char*)string, 0);
}
