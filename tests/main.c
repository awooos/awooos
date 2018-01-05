#include <flail.h>

// Trigger an intentional kernel panic.
// If there's something wrong, e.g. a recursive panic, it'll likely
// run indefinitely.
//
// On Travis CI, this will result in a build error after 10 minutes of
// printing no output.
//
// This isn't the most robust test, but it's good enough to ensure that
// panic() is behaving at least close to how it's expected to.
//
// NOTE: We use _flail_panic() instead of the usual flail_panic(), so we can pass
// "true", which indicates that it's an automated panic and the system
// should do a hard shutdown immediately after printing the panic
// information. (As opposed to the usual endless loop.)
void test_flail_intentional_panic()
{
    _flail_panic("This kernel panic is intentional.", __FUNCTION__, __FILE__, __LINE__, true);
}
