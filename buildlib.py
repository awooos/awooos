from fnmatch import filter as fnfilter
from pathlib import Path
import os

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
    if isinstance(command, list):
        command = recipe_expand(command)
    recipes[(target, match)] = (command, deps)

def task(target, deps, command):
    recipe(target, None, deps, command)
