#!/usr/bin/python3

from configparser import ConfigParser, ExtendedInterpolation
import inspect
from pathlib import Path
import shlex
from subprocess import check_output
import sys
from collections import UserDict

class Graph(UserDict):
    @property
    def vertices(self):
        return list(self.keys())

    @property
    def edges(self):
        edges = []
        for vertex, neighbors in self.data.items():
            for neighbor in neighbors:
                if {vertex, neighbor} not in edges:
                    edges.append({vertex, neighbor})
        return edges

    def get_vertex(self, vertex):
        if vertex in self.data:
            return self.data[vertex]
        else:
            return []

    def find_path(self, start, end, path=[]):
        # We've found the end of our path.
        if start == end:
            return path
        # If we can't find the first edge, the rest definitely doesn't exist.
        if start not in self.data:
            return None
        for node in self.data[start]:
            if node in path:
                continue
            new_path = self.find_path(node, end, path)
            if new_path:
                return new_path
        return None

    def dependencies(self, vertex, existing=[]):
        # If self.data[vertex] doesn't exist, or is empty, there's no deps.
        if len(self.get_vertex(vertex)) == 0:
            return []

        deps = []
        print(self.data[vertex])
        for deplist in self.data[vertex]:
            print("deplist =", deplist)
            for dep in deplist:
                print(vertex, dep, self.get_vertex(dep))
                if vertex in self.get_vertex(dep):
                    deps += self.get_vertex(dep)
                print(dep, deplist, existing)
                print(deps)
        return deps

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
    graph = Graph({
                'A': ['B', 'C'],
                'B': ['C', 'D'],
                'C': ['D'],
                'D': ['C'],
                'E': ['F'],
                'F': ['C']
    })

    deps = graph.dependencies('D')
    print(deps)
    assert(deps == ['A', 'B', 'C'])
    #exit(_main())
