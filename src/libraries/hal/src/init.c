#include <ali.h>
#include <ali/event.h>
#include <dmm.h>
#include <stddef.h>

extern char kernel_comment_start;

void hal_init(void *data)
{
    const char *metadata[] = {
        data,
        "\r\n",
        "Compiled with: ",
        &kernel_comment_start,
        NULL
    };

    ali_init(&_dmm_malloc, &_dmm_free, &_dmm_realloc);
    event_trigger("greeter display", metadata);
}
