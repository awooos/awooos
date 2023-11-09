TARGET ?= $(shell uname -m)

CC := clang
CLANG_CHECK := clang-check

SOURCES := $(wildcard src/*.c) platform-${TARGET}/main.c
CINCLUDES := -Iinclude

# TODO: Remove -Wno-reserved-identifier once that's resolved.
override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes \
					-Wno-documentation-unknown-command \
					-Wno-missing-noreturn \
					-Wno-reserved-identifier \
					-DFLAIL_DONT_DEFINE_STACK_DUMP=1

all: test

test/flail-test: $(SOURCES) #platform-${TARGET}/main.o
	${CC} ${CFLAGS} ${CINCLUDES} $^ test/main.c -o $@

test: test/flail-test
	pytest

lint:
	${CLANG_CHECK} $(filter %.c,${SOURCES}) -- ${CINCLUDES}

clean:
	rm -f **/*.o
	rm -f test/flail-test

.PHONY: all clean test
