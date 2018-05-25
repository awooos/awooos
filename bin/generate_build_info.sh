#!/bin/sh

TARGET_NORMAL="$2"
TARGET=$(echo "$2" | tr [a-z] [A-Z])

UPPER_CASE_BUILD_TYPE=$(echo "$1" | tr "[a-z]" "[A-Z]")
LOWER_CASE_BUILD_TYPE=$(echo "$1" | tr "[A-Z]" "[a-z]")

VERSION=$(git describe --tags HEAD --always)-${LOWER_CASE_BUILD_TYPE}

echo  "#ifndef AWOO_BUILD_INFO_H"
echo  "#define AWOO_BUILD_INFO_H"
echo  "#define AWOO_SCM_REV \"$(git show | head -n1 | cut -c8-)\""
echo  "#define AWOO_BUILD_TYPE \"${UPPER_CASE_BUILD_TYPE}\""
echo  "#define AWOO_VERSION \"${VERSION}\""
echo  "#define AWOO_TARGET_PRETTY \"${TARGET_NORMAL}\""
echo  "#define AWOO_TARGET \"${TARGET}\""
echo  "#define AWOO_${TARGET}"
echo  "#define AWOO_RELEASE_BUILD   0"
echo  "#define AWOO_DEBUG_BUILD     1"
echo  "#define AWOO_TEST_BUILD      2"
echo  "#define AWOO_BUILD_TYPE_NUMBER AWOO_${UPPER_CASE_BUILD_TYPE}_BUILD"
echo  "#endif"
