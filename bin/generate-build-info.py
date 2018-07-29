#!/usr/bin/env python3

import subprocess
import sys

build_type = sys.argv[1].upper()
target = sys.argv[2]
output_file = sys.argv[3]

version_or_rev_cmd = ["git", "describe", "--tags", "HEAD", "--always"]
version_or_rev = subprocess.check_output(version_or_rev_cmd).decode().strip()
version = "{}-{}".format(version_or_rev, build_type.lower())
scm_rev = subprocess.check_output(["git", "show"]).decode().split("\n")[0].split(" ")[1]

header = """
#ifndef KERNEL_BUILD_INFO_H
#define KERNEL_BUILD_INFO_H
#define KERNEL_SCM_REV \"{scm_rev}\"
#define KERNEL_BUILD_TYPE \"{build_type}\"
#define KERNEL_VERSION \"{version}\"
#define KERNEL_TARGET_PRETTY \"{target}\"
#define KERNEL_TARGET \"{uppercase_target}\"
#define KERNEL_{uppercase_target}
#define KERNEL_RELEASE_BUILD   0
#define KERNEL_DEBUG_BUILD     1
#define KERNEL_TEST_BUILD      2
#define KERNEL_BUILD_TYPE_NUMBER KERNEL_{build_type}_BUILD
#endif
""".lstrip()

with open(output_file, "w") as f:
    f.write(header.format(build_type=build_type,
            scm_rev=scm_rev,
            target=target,
            uppercase_target=target.upper(),
            version=version))

print("Build info file: {}".format(output_file))
