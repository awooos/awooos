.POSIX:

TARGET != ./target.sh

CC := clang
CLANG_CHECK := clang-check

SOURCES != echo src/*.c platform-${TARGET}/main.c
CINCLUDES := -Iinclude

CFLAGS := -std=c11 -pedantic-errors \
		-Wall -Wextra -Wconversion \
		-DFLAIL_DONT_DEFINE_STACK_DUMP=1

all: test

test/flail-test: ${SOURCES}
	${CC} ${CFLAGS} ${CINCLUDES} ${SOURCES} test/main.c -o $@

test: test/flail-test
	pytest

lint:
	${CLANG_CHECK} ${SOURCES} -- ${CINCLUDES}

clean:
	rm -f **/*.o
	rm -f test/flail-test

.PHONY: all clean test
