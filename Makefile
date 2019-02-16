CC := clang

SOURCES := $(wildcard src/*.c)

CINCLUDES := -I/usr/include -Ibuild/deps/tinker/include -Ibuild/deps/ali/include/ -Iinclude

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla

all: build/dmm-test

build-deps:
	mkdir -p build/deps/
	cd build/deps; test -d tinker || git clone https://github.com/awooos/tinker.git
	cd build/deps; test -d ali || git clone https://github.com/awooos/ali.git
	cd build/deps/tinker; git pull
	cd build/deps/ali; git checkout .; git pull
	cd build/deps/ali/include; rm std*.h

build/dmm-test: $(SOURCES)
	$(MAKE) build-deps
	${CC} ${CFLAGS} ${CINCLUDES} test/strrev.c $^ build/deps/tinker/src/main.c build/deps/ali/src/number/main.c test/main.c -o $@

test: build/dmm-test
	./build/dmm-test

clean:
	rm -rf build

.PHONY: all clean test build-deps
