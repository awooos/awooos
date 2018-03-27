#include <hal.h>
#include <stddef.h>

Hal_PanicFn *_hal_panic = NULL;

void hal_init(Hal_PanicFn *panic_fn)
{
    _hal_panic = panic_fn;
}
