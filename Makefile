CC := clang

SOURCES := $(wildcard src/*.c)

CINCLUDES := -Ibuild/deps/tinker/include -Iinclude

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla

all: build/dmm-test

build-deps:
	mkdir -p build/deps/
	cd build/deps; test -d tinker || git clone https://github.com/awooos/tinker.git
	cd build/deps/tinker; git pull

build/dmm-test: $(SOURCES)
	$(MAKE) build-deps
	${CC} ${CFLAGS} ${CINCLUDES} $^ build/deps/tinker/src/main.c test/main.c -o $@

test: build/dmm-test
	./build/dmm-test

clean:
	rm -rf build

.PHONY: all clean test build-deps
