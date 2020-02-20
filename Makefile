NAME := awoo
TARGET ?= i386
BUILD_TYPE ?= debug

CC := clang

SRCFILES := src/main.c
C_INCLUDES := -Iinclude
# TEST_SRCFILES := $(wildcard tests/*.c)

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2 -nostdinc     \
»···»···»···»···»···-fdiagnostics-show-option -Werror -Weverything   \
»···»···»···»···»···-Wno-cast-qual -Wno-missing-prototypes -Wno-vla


all:
	@echo "Available tasks:"
	@echo "  test"
	@echo "  lint"

test:
	echo "no tests yet"
	exit 1

lint:
	clang-check $(filter %.c,${SRCFILES}) -- ${C_INCLUDES}
