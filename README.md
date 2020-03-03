# Tinker

A low-level test framework for C code, which only requires a C11
compiler and a pointer to a `putchar()`-compatible function.

(It may work with a pre-C11 compiler, but this has not been tested.)

Source: https://github.com/awooos/tinker
Issues: https://github.com/awooos/tinker/issues


This makes it incredibly useful for testing memory managers, a libc
implementation, and other things.

## Usage

TODO: Actual good documentation.

For now, here's an example:

```
#include <stdio.h> // for putchar()

// unit test
void test_some_function() {
    bool result = some_function();

    if (result == 0) {
        tinker_pass()
    } else if (result == 1) {
        tinker_fail("Failure reason #1.");
    } else if (result == 2) {
        tinker_fail("Failure reason #2.");
    }
}

// collection of assertions.
void test_math() {
    tinker_assert(1 + 1 == 2);
    tinker_assert(1 - 1 == 0);
    tinker_assert(2 * 2 == 4);
    tinker_assert(4 / 2 == 2);
}

void test_unfinished() {
    tinker_skip("Not implemented.");
    return;

    // <test unfinished functionality here>
}

void add_tests() {
  tinker_add_test(some_function);
  tinker_add_test(math);
  tinker_add_test(unfinished);
}

int main() {
  add_tests();
  tinker_run_tests(&putchar);
}
```

## License

The code is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
