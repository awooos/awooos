# awooOS

awooOS is an experimental operating system, bringing together old ideas and
new technology.

It is designed around a microkernel, with as much moved into libraries
as possible. The kernel proper is less than 50 lines of code.

Notable features:

* [Docker](https://docker.com)-based build environment, for build consistency.
* Automated test suite, using Docker, Qemu, and a custom testing framework.
* Continuous integration using [Travis CI](https://travis-ci.org/).

## Development Dependencies

* Bash
* Docker

# Development

To clone the repository and run the test suite:

    $ git clone https://github.com/awooos/awooos.git
    $ cd awooos
    $ git submodule update --init

To update the repository, if you cloned it previously:

    $ git pull
    $ git submodule update

To run the test suite:

    $ ./bin/build-container
    $ ./bin/make clean test

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/duckinator/awooos.

## License

The code is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the awooOS project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/duckinator/awooos/blob/master/CODE_OF_CONDUCT.md).
