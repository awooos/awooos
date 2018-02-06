#!/bin/bash

DIR=$(dirname $(readlink -f $0)) # Directory script is in.
cd $DIR/../..

# Hard-code UID to 1000 so Jenkins is happy.
export WHALEDO_UID=1000
export BUILD_TYPE=nightly
export NAME_SUFFIX="-$(date +'%Y-%m-%d')"

./bin/make iso
