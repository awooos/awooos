# Tinker

A low-level test framework for C code, which only requires a partial libc
and a pointer to a `putchar()`-compatible function.

This makes it incredibly useful for testing memory managers, things like
a libc itself, etc.

Required headers:

| Header      | Required features | Notes |
|-------------|-------------------|-------|
| `stdbool.h` | `bool`            | Only used for the return type of `tinker_run_tests()` |
| `stddef.h`  | `size_t`          |       |
| `string.h`  | `strcpy()`        |       |
| `stdlib.h`  | Not sure? TBD     |       |

## Usage

TODO: Document the API.

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/awooos/tinker.

## License

The code is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the Tinker project's codebases, issue trackers,
chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/duckinator/awooos/blob/master/CODE_OF_CONDUCT.md).
