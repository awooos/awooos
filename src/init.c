#include <dmm.h>
#include <stddef.h>
#include "main.h"
#include "header.h"

DMM_PanicFn *_dmm_panic = NULL;

void dmm_init(DMM_PanicFn *panic_fn)
{
    _dmm_panic = panic_fn;
}
