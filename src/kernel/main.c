#include <eventually.h>
#include <kernel.h>

void kernel_main()
{
    greeter_register_events();
    tests_register_events();
    hal_register_events();

    eventually_event_trigger_immediate("HAL init", NULL, 0);
    eventually_event_trigger_immediate("greeter display", NULL, 0);
    eventually_event_trigger_immediate("tests run", NULL, 0);

    while(1){
        // Do nothing forever.
    }
}
