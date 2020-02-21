#!/bin/sh

SCM_REV=$(git describe --tags HEAD --always)

if [ "$1" = "test" ]; then
  TEST_BUILD=1
else
  TEST_BUILD=0
fi

echo  "#ifndef AWOO_BUILD_INFO_H"
echo  "#define AWOO_BUILD_INFO_H"
echo  "#define AWOO_SCM_REV       \"${SCM_REV}\""
echo  "#define AWOO_BUILD_TYPE    \"$1\""
echo  "#define AWOO_TARGET        \"$2\""
echo  "#define AWOO_TEST_BUILD    ${TEST_BUILD}"
echo  "#endif"
