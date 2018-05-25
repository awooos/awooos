#!/bin/sh

TARGET_PRETTY="$2"
TARGET=$(echo "$2" | tr [a-z] [A-Z])

BUILD_TYPE=$(echo "$1" | tr "[A-Z]" "[a-z]")

SCM_REV=$(git describe --tags HEAD --always)

if [ "${BUILD_TYPE}" == "test" ]; then
  TEST_BUILD=1
else
  TEST_BUILD=0
fi

echo  "#ifndef AWOO_BUILD_INFO_H"
echo  "#define AWOO_BUILD_INFO_H"
echo  "#define AWOO_SCM_REV       \"${SCM_REV}\""
echo  "#define AWOO_BUILD_TYPE    \"${BUILD_TYPE}\""
echo  "#define AWOO_TARGET        \"${TARGET}\""
echo  "#define AWOO_TARGET_PRETTY \"${TARGET_PRETTY}\""
echo  "#define AWOO_${TARGET}     1"
echo  "#define AWOO_TEST_BUILD    ${TEST_BUILD}"
echo  "#endif"
