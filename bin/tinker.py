#!/usr/bin/env python3

import re
import json
import sys

def header_source(repo):
    return "#include <{}.h>".format(repo["name"])

def initializer_source(repo):
    name = repo["name"]
    args = ", ".join(repo["initializeArgs"])

    return "    {}_init({});".format(name, args)

def runner_source(repo):
    name = repo["name"]

    if repo["run"] == False:
        return None
    else:
        return "    {}_run();".format(name)

def kernel_source(repos = []):
    headers = map(header_source, repos)
    initializers = map(initializer_source, repos)
    runners = map(runner_source, repos)
    runners = filter(lambda x: x != None, runners)

    kernel_source = "" + \
        "\n".join(headers) + "\n\n" + \
        "void tinker_kernel_main()\n" + \
        "{\n" + \
        "\n".join(initializers) + "\n" + \
        "\n".join(runners) + "\n" + \
        "}"

    return kernel_source

with open(sys.argv[1], "r") as f:
    config = json.load(f)

results = kernel_source(config)

print(results)
