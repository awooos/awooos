#include <ali/event.h>
#include <ali/text.h>
#include <flail.h>
#include "hal_flail.h"

void hal_flail_init(void *data)
{
    const char *kernel_info = (char*)data;

    flail_init(kernel_info, &print);

    event_trigger("register panic function", (void*)&_flail_panic);
}

