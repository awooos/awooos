#!/usr/bin/python3

from configparser import ConfigParser, ExtendedInterpolation
import inspect
from pathlib import Path
import shlex
from subprocess import check_output
import sys

class BuildConfig(ConfigParser):
    def __init__(self, config_file):
        super().__init__(interpolation=ExtendedInterpolation())
        self.read(config_file)

        platform = self["DEFAULT"]["build.platform"]
        self["platform"] = self["platform:" + platform]
        self["aliases"] = self._parse_aliases()
        print(list(self.items("aliases")))

    def _parse_aliases(self):
        aliases = dict([(k, v) for (k, v) in self.items("aliases")])
        print(aliases)
        for (k, v) in aliases.items():
            while v in aliases.keys() and v != k:
                aliases[k] = aliases[v]
                v = k
        return aliases

class Builder:
    def __init__(self, config_file):
        self.config = BuildConfig(config_file)

    def build_all(self, targets):
        return [self.build(target) for target in targets]

    def build(self, target):
        #command = self.commands[target]
        print("> {}".format(target))
        #print("$ {}".format(" ".join(command)))

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
    if len(args) == 0:
        targets = set(["all"])

    print("Targets:")
    for target in targets:
        print("- {}".format(target))

    builder = Builder("build.cfg")
    #builder.build_all(targets)

    return 0


if __name__ == "__main__":
    exit(_main())
