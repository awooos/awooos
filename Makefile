CC := clang
CLANG_CHECK := clang-check

SOURCES := $(wildcard src/*.c)

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes \
					-Wno-documentation-unknown-command

all: test

test/flail-test: $(SOURCES)
	${CC} ${CFLAGS} -Iinclude $^ test/main.c -o $@

test: test/flail-test
	pytest

lint:
	${CLANG_CHECK} $(filter %.c,${SOURCES}) -- ${CINCLUDES}

clean:
	rm -f test/flail-test

.PHONY: all clean test
