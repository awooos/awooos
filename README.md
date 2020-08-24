# flail

A library for implementing kernel panics.

## Requirements

1. An `stddef.h` which defines `size_t`.
2. A `putchar()`-equivalent. It does not need to have any specific name.
   * Accepts a single `int` and, presumably, prints it (after casting to an `unsigned char`).
   * The return value isn't used, but I recommend following the POSIX/C standards.

## Usage

```c
#include <flail.h> /* Note: flail.h uses stddef.h. */

// Operating system information to include in the panic message.
const char *info_str = "Some Operating System v1.0";

int custom_putchar(int c)
{
  // Implement me!
  return c; // It "worked."
}

void kernel_main()
{
    flail_init(info_str, &custom_putchar);
    flail_panic("oh no");
}
```

## License

The code is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
