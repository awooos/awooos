# awooOS

awooOS is an experimental operating system, bringing together old ideas and
new technology.

It is designed around a microkernel, with as much moved into libraries
and services as possible. The kernel proper is less than 50 lines of code.

Notable features:

* [Docker](https://docker.com)-based build environment, for builds consistency.
* Automated test suite, using Docker, Qemu, and a custom testing framework.
* Continuous integration using [Travis CI](https://travis-ci.org/).

## Development Dependencies

* Docker
* Python, with pip

# Development

    $ pip install whaledo # Required for ./bin/make.
    $ ./bin/make clean test

This'll run the test suite in Docker and print the results.

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/duckinator/awooos.

## License

The code is available as open source under the terms of the [Mozilla Public License 2.0](https://opensource.org/licenses/MPL-2.0).

## Code of Conduct

Everyone interacting in the awooOS project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/duckinator/awooos/blob/master/CODE_OF_CONDUCT.md).
