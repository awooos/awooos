#include <awoo.h>
#include <ali/event.h>
#include <greeter.h>
#include <hal.h>
#include <shell.h>
#include <stdnoreturn.h>
#include <tests.h>

noreturn void kernel_main()
{
    bool test_build = (AWOO_BUILD_TYPE_NUMBER == AWOO_TEST_BUILD);

    greeter_register_events();
    tests_register_events();
    hal_register_events();

    event_trigger("HAL init", (void*)AWOO_INFO);
    event_trigger("tests run", &test_build);

    shell_init();

    while(1){
        // Do nothing forever.
    }
}
