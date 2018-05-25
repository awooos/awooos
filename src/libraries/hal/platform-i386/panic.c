#include <stddef.h>
#include "panic.h"

Hal_PanicFn *_hal_panic = NULL;

void hal_panic_init(Hal_PanicFn *panicfn)
{
    _hal_panic = panicfn;
}