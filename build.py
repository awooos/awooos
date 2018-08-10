#!/usr/bin/python3

from configparser import ConfigParser, ExtendedInterpolation
import inspect
from pathlib import Path
from subprocess import check_output
import sys

def config_parser(config_file):
    parser = ConfigParser(interpolation=ExtendedInterpolation())
    with open(config_file) as f:
        parser.read_file(f)
    return parser

class BuildCommands:
    def __init__(self, config):
        self.config = config
        self.commands = {}
        self.add_all(self.config)

    def add_all(self, config):
        print(config.sections())
        pass

    def add(self, command):
        pass

class Builder:
    def __init__(self, config_file):
        self.config = config_parser(config_file)
        self.commands = BuildCommands(self.config)

    def build_all(self, targets):
        return [self.build(target) for target in targets]

    def build(self, target):
        pass

def _main(argv = None):
    """
    TODO: Documentation.
    """
    argv = argv or sys.argv
    args = argv[1:]
    if "--help" in args or "-h" in args:
        print(inspect.getdoc(_main))
        return 1

    targets = set(args)
    if len(targets) == 0:
        targets.update(["all"])

    print("Targets:")
    for target in targets:
        print("- {}".format(target))

    builder = Builder("build.cfg")
    builder.build_all(targets)

    return 0


if __name__ == "__main__":
    exit(_main())
