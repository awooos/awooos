NAME := awoo
TARGET ?= i386
BUILD_TYPE ?= debug

CC := clang

SRCFILES := $(wildcard src/*.c)
C_INCLUDES := -Iinclude
TEST_SRCFILES := $(wildcard test/*.c)

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2               \
					-fdiagnostics-show-option -Werror -Weverything   \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla  \
					-Wno-documentation-unknown-command               \
					-Wno-extra-semi-stmt


all:
	@echo "Available tasks:"
	@echo "  test"
	@echo "  lint"

./tinker-test:
	${CC} ${CFLAGS} ${C_INCLUDES} ${SRCFILES} ${TEST_SRCFILES} -o $@

test: ./tinker-test
	./tinker-test

lint:
	clang-check ${SRCFILES} ${TEST_SRCFILES} -- ${C_INCLUDES}

clean:
	rm -f tinker-test

.PHONY: all clean test
