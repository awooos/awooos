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
long test_some_function() {
    some_function();

    if (!<some test condition>) {
        // Using TEST_FATAL fails the test and stops the test suite immediately.
        TEST_RETURN(TEST_FATAL, "Failure reason");
    }

    if (!<some other test condition>) {
        // Using TEST_FAILURE fails the test, but lets the test suite continue.
        TEST_RETURN(TEST_FAILURE, "Failure reason");
    }

      // Using TEST_SUCCESS indicates that the test passed.
      TEST_RETURN(TEST_SUCCESS, "Success message");
}

// collection of assertions.
long test_math() {
    // Does some initial setup that `TEST_ASSERT()` requires.
    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(1 + 1 == 2);
    TEST_ASSERT(1 - 1 == 0);
    TEST_ASSERT(2 * 2 == 4);
    TEST_ASSERT(4 / 2 == 2);

    // Does cleanup and prints the results.
    TEST_ASSERTIONS_RETURN();
}

void add_tests() {
  tinker_add_test(some_function);
  tinker_add_test(math);
}

int main() {
  add_tests();
  tinker_run_tests(putchar);
}
```

## License

The code is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
