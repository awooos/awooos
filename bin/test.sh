#!/bin/bash

NAME=dux
PORT=9876


DIR=$(dirname $(readlink -f $0)) # Directory script is in
cd $DIR

QEMU=$1

if [ -z "$QEMU" ]; then
  QEMU=qemu-system-i386
fi

# Flags that should be able to be passed but can't, for some reason: -nographic -pidfile "$NAME.pid"
$QEMU -cpu core2duo -m 32M -usb -serial "tcp::$PORT,server" -name "$NAME" -monitor null  -daemonize -no-reboot -cdrom "iso/$NAME.iso" -pidfile "$NAME.pid" &

sleep 1

{ sleep 10; echo 'h'; } | nc localhost $PORT &> tests.raw


cat tests.raw | awk '
BEGIN {
	print "Beginning testing."

	FS=" ";
	PASSED=0;
	FAILED=0;
}
/BEGIN TESTS/,/END TESTS/ {
	if ($1 == "PASS:") {
		printf ".";
		PASSED++;
	}
	
	if ( $1 == "FAIL:" ) {
		printf ("\n%s\n", $0);
		FAILED++;
	}
}
END {
	print "\nFinished testing."
	printf ("Test results: %d passed, %d failed, %d total.\n", PASSED, FAILED, PASSED + FAILED);
}\
' &> tests.out

echo
cat tests.out
echo
echo "DEBUG (tests.raw):"
cat tests.raw
echo


PID=$(cat $NAME.pid)

PID_EXISTS=false
if [ -f "$NAME.pid" ]; then
  PID_EXISTS=true
fi

# Kill off the qemu process if it's still running
kill -0 $PID 2>/dev/null && kill $PID
rm "$NAME.pid"

if ! $PID_EXISTS || cat tests.out | grep -E "^FAIL: " &>/dev/null; then
  exit 1
else
  exit 0
fi
