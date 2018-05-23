#include <awoo.h>
#include <ali/event.h>
#include <shell.h>
#include <stdnoreturn.h>

typedef void (constructor)();

extern size_t __CTOR_LIST__;

noreturn void kernel_main()
{
    bool test_build = (AWOO_BUILD_TYPE_NUMBER == AWOO_TEST_BUILD);

    // Run all of the constructors.
    constructor **ctors = (constructor**)&__CTOR_LIST__;
    for (size_t i = 0; ctors[i] != NULL; i++) {
        ctors[i]();
    }

    event_trigger("HAL init", (void*)AWOO_INFO);
    event_trigger("tests run", &test_build);

    shell_init();

    while(1){
        // Do nothing forever.
    }
}
