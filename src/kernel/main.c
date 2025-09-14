#include <awoo.h>
#include <awoo/tests.h>
#include <hal.h>
#include <timer.h>
#include <ali/event.h>
#include <stdnoreturn.h>

typedef void (constructor)(void);

extern void shell_init(void); // FIXME: this should eventually become a process

noreturn void kernel_main()
{
    bool test_build = (AWOO_TEST_BUILD == 1);

    hal_init();
    timer_init();
    tests_run(test_build);
    shell_init();

    while(1){
        // Do nothing forever.
    }
}
