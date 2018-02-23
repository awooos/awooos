#include <flail.h>

// Trigger an intentional kernel panic.
// If there's something wrong, e.g. a recursive panic, it'll likely
// run indefinitely.
//
// On Travis CI, this will result in a build error after 10 minutes of
// printing no output.
//
// This isn't the most robust test, but it's better than nothing.
//
// NOTE: We use _flail_print_panic() instead of the usual flail_panic() so
//       we can continue running after the fake panic.
void test_flail_intentional_panic()
{
    _flail_print_panic("This kernel panic is intentional.", __FUNCTION__, __FILE__, __LINE__);
}
