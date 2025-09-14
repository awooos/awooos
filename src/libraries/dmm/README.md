# DMM

A memory management library, made for [awooOS](https://github.com/awooos/awooos).

DMM supports multiple simultaneous instances, allowing you to
manage different sections of memory independently. It also provides a
simpler API, if you wish to use a single instance.

The multi-instance version isn't documented yet. (Sorry about that.)

## Requirements

1. A valid `stddef.h` and `stdint.h` (usually provided by libc).
2. A "panic" function (see below).

The panic function must have the following signature:

```c
void _panic(const char *message, const char *function,
            const char *filename, size_t line);
```

## Basic Usage (global instance)

If you want just a single DMM instance, you can do the
following:

```c
#include <dmm.h>    // pulls in <stddef.h>
#include <stdlib.h> // for exit()

void _panic(const char *message, const char *function,
            const char *filename, size_t line) {
    // Loosely based on Rust's panic message format.
    fprintf(stderr, "function '%s' panicked at '%s', %s:%zu\n", function, message, filename, line);
    exit(1);
}

int main(void) {
    char *region1 = malloc(10);
    char *region2 = malloc(512);
    char *region3 = malloc(1024);

    dmm_init(&_panic);

    dmm_add_memory_region(region1, 10);
    dmm_add_memory_region(region2, 512);
    dmm_add_memory_region(region3, 1024);

    dmm_malloc(9);   // can be from any region
    dmm_malloc(100); // can be from region2 or region3
    dmm_malloc(600); // can only be from region3.

    // Clean up after ourselves.
    free(region1);
    free(region2);

    return 0;
}
```

## Advanced Usage (multiple instances)

TODO.

# License

The code is available as open source under the [MIT
License](https://github.com/awoos/dmm/raw/master/LICENSE.txt).
