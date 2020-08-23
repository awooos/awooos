CC := clang
CLANG_CHECK := clang-check

SOURCES := $(wildcard src/*.c)

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla \
					-Wno-documentation-unknown-command \
					-Wno-extra-semi-stmt \
					-Wno-unknown-warning-option

all: test

test/flail-test: $(SOURCES)
	${CC} ${CFLAGS} -Iinclude $^ test/main.c -o $@

test: test/flail-test
	pytest

lint:
	${CLANG_CHECK} $(filter %.c,${SOURCES}) -- ${CINCLUDES}

clean:
	rm -rf build

.PHONY: all clean test
