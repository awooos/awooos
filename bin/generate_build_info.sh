#!/bin/sh

TARGET_PRETTY="$2"
TARGET=$(echo "$2" | tr [a-z] [A-Z])

UPPER_CASE_BUILD_TYPE=$(echo "$1" | tr "[a-z]" "[A-Z]")
LOWER_CASE_BUILD_TYPE=$(echo "$1" | tr "[A-Z]" "[a-z]")

SCM_REV=$(git describe --tags HEAD --always)

echo  "#ifndef AWOO_BUILD_INFO_H"
echo  "#define AWOO_BUILD_INFO_H"
echo  "#define AWOO_SCM_REV \"${SCM_REV}\""
echo  "#define AWOO_BUILD_TYPE \"${UPPER_CASE_BUILD_TYPE}\""
echo  "#define AWOO_PRETTY_BUILD_TYPE \"${LOWER_CASE_BUILD_TYPE}\""
echo  "#define AWOO_TARGET \"${TARGET}\""
echo  "#define AWOO_TARGET_PRETTY \"${TARGET_PRETTY}\""
echo  "#define AWOO_${TARGET}"
echo  "#define AWOO_RELEASE_BUILD   0"
echo  "#define AWOO_DEBUG_BUILD     1"
echo  "#define AWOO_TEST_BUILD      2"
echo  "#define AWOO_BUILD_TYPE_NUMBER AWOO_${UPPER_CASE_BUILD_TYPE}_BUILD"
echo  "#endif"
