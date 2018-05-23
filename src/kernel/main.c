#include <awoo.h>
#include <ali/event.h>
#include <greeter.h>
#include <hal.h>
#include <shell.h>
#include <stdnoreturn.h>
#include <tests.h>

#include <ali/text.h>
#include <ali/number.h>
typedef void (autorun_fn)();

extern size_t __CTOR_LIST__;
extern size_t __CTOR_END__;

autorun_fn **get_kernel_autorun_start()
{
    return (autorun_fn**)(&__CTOR_LIST__ + 1);
}

autorun_fn **get_kernel_autorun_end()
{
    return (autorun_fn**)&__CTOR_END__;
}

noreturn void kernel_main()
{
    bool test_build = (AWOO_BUILD_TYPE_NUMBER == AWOO_TEST_BUILD);

    autorun_fn **ctors = get_kernel_autorun_start();
    for (size_t i = 0; ctors[i] != NULL; i++) {
        ctors[i]();
    }

//    greeter_register_events();
    tests_register_events();
    hal_register_events();

    event_trigger("HAL init", (void*)AWOO_INFO);
    event_trigger("tests run", &test_build);

    shell_init();

    while(1){
        // Do nothing forever.
    }
}
