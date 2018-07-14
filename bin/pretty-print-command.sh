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

PADDING_STR="      "
OK_STRING="[OK]  "
ERR_STRING="[ERR] "
WARN_STRING="[WARN]"

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

function print_message() {
  printf "%b" "$1 ${MSG_COLOR}${STR} ${OBJ_COLOR}${NAME}${NO_COLOR}"
}

function print_message_r() {
  printf "%b" "\r"
  print_message "$1"
  printf "%b" "\n"
}

print_message "$PADDING_STR"

${COMMAND} &> "$NAME.log"
RESULT=$?

if [ $RESULT -ne 0 ]; then
    print_message_r "${ERR_COLOR}${ERR_STRING}"
elif [ -s "$NAME.log" ] && [ "$TYPE" != "ISO" ]; then
    print_message_r "${WARN_COLOR}${WARN_STRING}"
else
    print_message_r "${OK_COLOR}${OK_STRING}"
fi
cat -- "$NAME.log"
rm -f -- "$NAME.log"

exit $RESULT
