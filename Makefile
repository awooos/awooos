CC := clang

SOURCES := $(wildcard src/*.c)
TEST_SOURCES := test/main.c

CINCLUDES := -Ibuild/deps/tinker/include -Iinclude

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla \
					-Wno-documentation-unknown-command

all: build/dmm-test

build-deps:
	mkdir -p build/deps/
	cd build/deps; test -d tinker || git clone https://github.com/awooos/tinker.git
	cd build/deps/tinker; git pull

build/dmm-test: $(SOURCES)
	$(MAKE) build-deps
	${CC} ${CFLAGS} ${CINCLUDES} $^ build/deps/tinker/src/main.c ${TEST_SOURCES} -o $@

test: build/dmm-test
	./build/dmm-test

lint: build-deps
	clang-check ${SOURCES} ${TEST_SOURCES} -- ${CINCLUDES}

clean:
	rm -rf build

.PHONY: all clean test build-deps
