#include <ali/event.h>
#include <greeter.h>
#include <hal.h>
#include <shell.h>
#include <stdnoreturn.h>
#include <tests.h>

noreturn void kernel_main()
{
    greeter_register_events();
    tests_register_events();
    hal_register_events();

    event_trigger("HAL init", NULL);
    event_trigger("tests run", NULL);

    shell_init();

    while(1){
        // Do nothing forever.
    }
}
