#!/bin/sh

# Helper script for pretty Makefile output.

TYPE="$1"
NAME="$2"
COMMAND=$(echo $@ | cut -d ' ' -f 3-)

MSG_COLOR="\033[0;34m"
OBJ_COLOR="\033[0;36m"
OK_COLOR="\033[0;32m"
ERR_COLOR="\033[0;31m"
WARN_COLOR="\033[0;33m"
NO_COLOR="\033[m"

PADDING_STR="       "
OK_STRING="[OK]"
ERR_STRING="[ERR]"
WARN_STRING="[WARN]"
CC_STRING="CC   "
AS_STRING="AS   "
ISO_STRING="ISO  "
LINT_STRING="LINT "

case $TYPE in
CC)
    STR="CC  ";;
AR)
    STR="AR  ";;
AS)
    STR="AS  ";;
LD)
    STR="LD  ";;
ISO)
    STR="ISO ";;
LINT)
    STR="LINT";;
esac

printf "%b" "${PADDING_STR}${MSG_COLOR}${STR}${OBJ_COLOR}${NAME}${NO_COLOR}"

${COMMAND} &> "$NAME.log"
RESULT=$?

if [ $RESULT -ne 0 ]; then
    printf "%b" "\r${ERR_COLOR}${ERR_STRING}${NO_COLOR}\n";
elif [ -s "$NAME.log" ] && [ "$TYPE" != "ISO" ]; then
    printf "%b" "\r${WARN_COLOR}${WARN_STRING}${NO_COLOR}\n";
else
    printf "%b" "\r${OK_COLOR}${OK_STRING}${NO_COLOR}\n";
fi
cat -- "$NAME.log"
rm -f -- "$NAME.log"

exit $RESULT
