#include <eventually.h>
#include <kernel.h>
#include <awoo/modifiers.h>

noreturn kernel_main()
{
    greeter_register_events();
    tests_register_events();
    hal_register_events();

    event_trigger("HAL init", NULL, 0);
    event_trigger("greeter display", NULL, 0);
    event_trigger("tests run", NULL, 0);

    while(1){
        // Do nothing forever.
    }
}
