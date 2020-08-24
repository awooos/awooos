#include <flail.h>
#include <flail/internal.h>

// Trigger most of a kernel panic.
//
// This calls `_flail_print_panic()` directly instead of calling
// `flail_panic()`, so it doesn't hang forever.
void test_flail_intentional_panic()
{
    _flail_print_panic("This kernel panic is intentional.", __FUNCTION__, __FILE__, __LINE__);
}
