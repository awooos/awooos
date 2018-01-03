#!/bin/bash

docker run -v "$(pwd):/tmp/work" -w /tmp/work whaledo/os-development-x86 BUILD_TYPE=nightly NAME_SUFFIX="-$(date +'%Y-%m-%d') iso
