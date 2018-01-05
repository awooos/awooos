# flail

A library for implementing kernel panics.

## Requirements

1. An `stddef.h` which defines `size_t`.
2. A `puts()`-equivalent. It does not need to have any specific name.
   * Accepts a single `const char*` and, presumably, prints it.
   * Returns a non-negative number on success, or `-1` on error.

## Usage

```
#include <flail.h> /* Note: flail.h uses stddef.h. */

// Operating system information to include in the panic message.
const char *info_str = "Some Operating System v1.0";

int puts(const char *puts)
{
  // Implement me!
  return 0; // It "worked."
}

void kernel_main()
{
    flail_init(info_str, &puts);
    flail_panic("oh no");
}
```

## License

The code is available as open source under the terms of the [MIT License](https://opensource.org/license/MIT).
