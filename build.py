#!/usr/bin/python3

from configparser import ConfigParser, ExtendedInterpolation
import inspect
from pathlib import Path
from subprocess import check_output
import sys

def load_config(config_file):
    config = ConfigParser(interpolation=ExtendedInterpolation())
    with open(config_file) as f:
        config.read_file(f)

    platform = config["DEFAULT"]["build.platform"]
    config["platform"] = config["platform:" + platform]

    return config

class BuildCommands:
    def __init__(self, config):
        self.config = config
        self.commands = {}
        self.aliases = {}
        self.add_all(self.config)
        self._add_aliases(self.config["aliases"])

    def add_all(self, config):
        for section_name in config.sections():
            section = config[section_name]
            if "command" in section:
                self.add(section_name, section["command"])

    def add(self, section_name, command):
        self.commands[section_name] = command

    def _add_aliases(self, aliases):
        for alias, value in aliases.items():
            self.aliases[alias] = value

    def category_for(self, name):
        if "." in name:
            category = name.split(".", 1)[0]
        else:
            category = name

        category = "categories:{}".format(category)

        if not category in self.config["project"]["categories"]:
            return (None, None)
        return (category, name)

    def category_command_format(self, category_name, name):
        category = self.config[category_name]
        command = category["command"]
        values = {
            "category": category_name,
            "name": name,
            "artifacts.c": ["???.c.o"],
            "artifacts.asm": ["???.asm.o"],
        }
        return [arg.format(**values) for arg in command]

    def category_command(self, name):
        category, name = self.category_for(name)
        if category is None:
            print("error: Unknown category: {}".format(category))
            exit(1)
        return self.category_command_format(category, name)

    def __getitem__(self, name):
        if name in self.aliases:
            # TODO: Avoid infinite loops if people do silly things.
            return self.__getitem__(self.aliases[name])
        elif name in self.commands:
            return self.commands[name]
        elif self.category_for(name):
            return self.category_command(name)
        else:
            print("error: No such target: {}".format(name))
            exit(1)

class Builder:
    def __init__(self, config_file):
        self.config = load_config(config_file)
        self.commands = BuildCommands(self.config)

    def build_all(self, targets):
        return [self.build(target) for target in targets]

    def build(self, target):
        print("[{}]: {}".format(target, self.commands[target]))

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
