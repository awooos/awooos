#!/usr/bin/env python

from datetime import datetime
import whaledo

date = datetime.now().strftime("%Y-%m-%d")

contents = None
with open("include/awoo/build_info.h", "r") as f:
    contents = f.read()

lines = contents.split("\n")

version_line = next((x for x in lines if "AWOO_VERSION" in x), None)
version = version_line.split(" ")[2]

iso_name = "awoos-{}-{}.iso".format(date, version)

command = ["make", "BUILD_TYPE=nightly", "clean", "iso"]
status = whaledo.run("os-development-x86", command)

if status != 0:
    exit(status)

# TODO: Upload to DigitalOcean.

exit(status)
