CC := clang

SOURCES2 := $(wildcard src/*.c src/*/*.c src/*/*/*.c)
SOURCES := src/main.c src/main_test.c \
			src/nonstandard/str/test.c \
			src/nonstandard/number/main.c src/nonstandard/number/main_test.c \
			src/nonstandard/str/shellsplit.c src/nonstandard/str/shellsplit_test.c \
			src/nonstandard/str/charsplit.c src/nonstandard/str/charsplit_test.c \
			src/string_to_integer.c src/string_to_integer_test.c \
			src/string.c src/string_test.c \
			src/math.c src/math_test.c \
			src/event.c src/assert.c src/text.c

CINCLUDES := -Ibuild/deps/tinker/include -Iinclude

override CFLAGS += -std=c11 -pedantic-errors \
					-DALI_PUTCHAR_NAME=_ali_putchar \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla \
					-Wno-documentation-unknown-command \
					-Wno-extra-semi-stmt \
					# -nodefaultlibs -lc \

all: build/ali-test

build-deps:
	mkdir -p build/deps/
	cd build/deps; test -d tinker || git clone https://github.com/awooos/tinker.git
	cd build/deps/tinker; git pull

build/ali-test: $(SOURCES)
	$(MAKE) build-deps
	${CC} ${CFLAGS} ${CINCLUDES} $^ build/deps/tinker/src/main.c test/main.c -o $@

test: build/ali-test
	./build/ali-test

clean:
	rm -rf build

.PHONY: all clean test build-deps
