#!/usr/bin/env bash

# Stop on first error
set -e

REPONAME="awooos-builder"
TAG="latest"
MOUNTS="-v $(pwd):/tmp/build -w /tmp/build"

image=$(docker images --format "{{.Repository}}\t{{.Tag}}\t{{.CreatedAt}}" "${REPONAME}:${TAG}")

if [ -n "${image}" ]; then
    echo "${REPONAME} found, not rebuilding."
    echo "Remove the existing container if you want to force a rebuild."
else
    echo "${REPONAME} not found, building..."
    docker build . -t "${REPONAME}"
fi

for real_arg in "$@"; do
  arg="$real_arg"

  adjusted=false
  case $arg in
    qemu*|bochs|vbox)
      arg="all"
      adjusted=true
  esac

  docker run --rm -it ${MOUNTS} -u $(id -u) "${REPONAME}" "$arg"

  if $adjusted; then
    make "$real_arg"
  fi
done
