#!/usr/bin/env bash

# Stop on first error
set -e

REPONAME="awooos-builder"
TAG="latest"
MOUNTS="-v $(pwd):/tmp/build -w /tmp/build"

image=$(docker images --format "{{.Repository}}\t{{.Tag}}\t{{.CreatedAt}}" "${REPONAME}:${TAG}")

[ -n "${image}" ]       && BUILD=true
if [ "$1" == "--build" ]; then
  BUILD=true
  shift
fi

if $BUILD; then
    echo "Building ${REPONAME} Docker image..."
    docker build . -t "${REPONAME}"
fi

docker run --rm -it ${MOUNTS} -u $(id -u) "${REPONAME}" "$@"
