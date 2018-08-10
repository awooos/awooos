#!/usr/bin/python3

from configparser import ConfigParser, ExtendedInterpolation
import inspect
from pathlib import Path
from subprocess import check_output
import sys

def config_parser(config_file):
    parser = ConfigParser(interpolation=ExtendedInterpolation())
    parser.read_file(config_file)
    return parser

class BuildCommands:
    def __init__(self):
        self.commands = {}

class Builder:
    def __init__(self, config_file):
        config = config_parser(config_file)

def _main(argv = None):
    """
    TODO: Documentation.
    """
    argv = argv or sys.argv
    args = argv[1:]
    if "--help" in args or "-h" in args:
        print(inspect.getdoc(_main))
        return 1

    arg_vars = {}
    targets  = []
    for arg in args:
        if arg[0] == "-":
            print("error: Unknown flag: {}".format(arg), file=sys.stderr)
            return 1
        elif "=" in arg:
            key, val = arg.split("=", 1)
            arg_vars[key] = val
        else:
            targets.append(arg)

    if len(targets) == 0:
        targets = ["all"]

    print("Overridden variables:")
    for key, val in arg_vars.items():
        print("- {} = {}".format(key, val))
    print("")

    print("Targets:")
    for target in targets:
        print("- {}".format(target))

    # TODO: Actually build things.

    return 0


if __name__ == "__main__":
    exit(_main())
