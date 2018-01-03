#!/bin/bash

# Hard-code UID to 1000 so Jenkins is happy.
docker run -v "$(pwd):/tmp/work" -w /tmp/work --env-file env.whaledo -u 1000 whaledo/os-development-x86 make BUILD_TYPE=nightly NAME_SUFFIX="-$(date +'%Y-%m-%d')" iso
