from fnmatch import filter as fnfilter
from pathlib import Path
import os
import shlex
import sys

def env(key, default=None):
    return os.environ.get(key, default)


# Miscellaneous file suffix manipulation stuff.

def is_filetype(suffix):
    return lambda x: x.endswith(suffix)


def with_suffix(suffix):
    return lambda x: str(Path(x).with_suffix(suffix))

# Recipes

def recipe_expand(command):
    def cmd(target, match, deps):
        return [x.format(target=target, match=match, deps=deps)
                for x in command]
    return cmd


recipes = {}
def recipe(target, match, deps, command):
    deps = set(deps)
    if isinstance(command, str):
        command = shlex.split(command)
    if isinstance(command, list):
        command = recipe_expand(command)
    recipes[target] = (match, deps, command)


def task(target, deps, command):
    recipe(target, None, deps, command)



# Stuff for executing recipes.

def find_recipe(target):
    for target_pattern in recipes:
        recipe = recipes[target_pattern]
        match, deps, command = recipe
        pattern_parts = target_pattern.split(".")
        if target == target_pattern:
            print("1. {} == {}".format(target, target_pattern))
            return recipe
        elif len(pattern_parts) == 2 and pattern_parts[0] == "%" \
                and pattern_parts[1] == target.split(".")[-1]:
            print("2. {} ~= {}".format(target, target_pattern))
            return recipe
        else:
            print("{} != {}".format(target, target_pattern))


def run_recipe(target):
    if target is None:
        return
    recipe = find_recipe(target)
    if recipe is None:
        print("No rule for target: {}".format(target), file=sys.stderr)
        exit(1)
    match, deps, command = recipe
    print("FOUND: {} => {}".format(target, len(deps)))
    print("")
    [run_recipe(dep) for dep in deps]


_default = None
def default(name):
    global _default
    _default = name
    print("New default: {}".format(_default))
    return _default


def build(argv=None):
    argv = argv or sys.argv
    if len(argv) > 1:
        args = argv[1:]
    else:
        args = [_default]
    return [run_recipe(arg) for arg in args]
