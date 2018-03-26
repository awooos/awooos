#include <stdnoreturn.h>
#include <ali/event.h>
#include <kernel.h>
#include <tinker.h>
#include <awoo/modifiers.h>

noreturn void kernel_main()
{
    greeter_register_events();
    tests_register_events();
    hal_register_events();
    tinker_init(&kprint);

    event_trigger("HAL init", NULL, 0);
    event_trigger("greeter display", NULL, 0);
    event_trigger("tests run", NULL, 0);

    while(1){
        // Do nothing forever.
    }
}
