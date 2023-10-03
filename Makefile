CC := clang

SRCFILES := src/main.c
C_INCLUDES := -Iinclude
TEST_SRCFILES := test/main.c test/test_tinker_assert.c test/test_tinker_uint_to_str.c

CFLAGS += -std=c11 -pedantic-errors -gdwarf-2               \
			-fdiagnostics-show-option -Werror -Weverything   \
			-Wno-unknown-warning-option \
			-Wno-cast-qual -Wno-missing-prototypes \
			-Wno-documentation-unknown-command  \
			-Wno-unsafe-buffer-usage


all: tinker-test

tinker-test:
	${CC} ${CFLAGS} ${C_INCLUDES} ${SRCFILES} ${TEST_SRCFILES} -o $@

test: tinker-test
	./tinker-test

lint:
	clang-check ${SRCFILES} ${TEST_SRCFILES} -- ${C_INCLUDES}

clean:
	rm -f tinker-test

.PHONY: all clean test
