CC := clang
CLANG_CHECK := clang-check

SOURCES := $(wildcard src/*.c)
CINCLUDES := -Iinclude

TARGET ?= $(shell uname -m)

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes \
					-Wno-documentation-unknown-command

all: test

platform-i386/%.o: platform-i386/%.asm
	nasm -felf32 -o $@ $<

platform-x86_64/%.o: platform-x86_64/%.asm
	nasm -felf64 -o $@ $<

test/flail-test: $(SOURCES) #platform-${TARGET}/main.o
	${CC} ${CFLAGS} ${CINCLUDES} $^ test/main.c -o $@

test: test/flail-test
	pytest

lint:
	${CLANG_CHECK} $(filter %.c,${SOURCES}) -- ${CINCLUDES}

clean:
	rm -f test/flail-test

.PHONY: all clean test
