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

docker run --rm -it ${MOUNTS} -u $(id -u) "${REPONAME}" "$@"
