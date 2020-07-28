CC := clang
CLANG_CHECK := clang-check

SOURCES := $(wildcard src/*.c src/*/*.c src/*/*/*.c)
CINCLUDES := -Ibuild/deps/tinker/include -Iinclude

override CFLAGS += -std=c11 -pedantic-errors \
					-DALI_PUTCHAR_NAME=ali_putchar \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla \
					-Wno-documentation-unknown-command \
					-Wno-extra-semi-stmt \
					-Wno-unknown-warning-option

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

lint: build-deps
	${CLANG_CHECK} $(filter %.c,${SOURCES}) -- ${CINCLUDES}

clean:
	rm -rf build/ali-test

veryclean:
	rm -rf build

.PHONY: all clean veryclean test build-deps
