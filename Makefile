NAME := awoo

BUILD_TYPE ?= debug

ISO_DIR  ?= iso/
ISO_FILE ?= ${ISO_DIR}/${NAME}-${TARGET}.iso

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2 -nostdinc -ffreestanding -fno-stack-protector -fno-builtin -fdiagnostics-show-option -Wall -Wextra -Wpedantic -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration -Iinclude

override LDFLAGS += -nostdlib -g

override ASFLAGS +=

# If config.mk doesn't exist, it triggers the corresponding rule.
# If ${TARGET} is undefined, this triggers the "make/.mk" rule.
#
# Also, the LAST INCLUDED FILE is attempted first, because... reasons?
# So we need config.mk last.
include make/despair.mk
include config.mk
include make/${TARGET}.mk

# == Begin gross bullshit for only matching things for the current platform. ==

# We're searching for .c and .asm files.
SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'

# E.g. src/bootstrap/i386, src/libraries/hal-i386, etc.
#      (But for the specific target we're building for.)
INCLUDE_CURRENT_TARGET_DIRECTORIES := '(' -wholename 'src/*/${TARGET}/*' -o -wholename 'src/*/*-${TARGET}/*' ')'

# Ignore things that are target-specific.
EXCLUDE_ALL_TARGET_DIRECTORIES := '(' '!' -wholename 'src/*/*-*/*' -a '!' -wholename 'src/bootstrap/*' ')'

# == End gross bullshit for only matching things for the current platform.   ==

SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES} '(' ${EXCLUDE_ALL_TARGET_DIRECTORIES} -o ${INCLUDE_CURRENT_TARGET_DIRECTORIES} ')')
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, ${SRCFILES}))

BUILDINFO := $(shell ./bin/build_info.sh ${BUILD_TYPE} ${TARGET} > ./include/awoo/build_info.h)

all: src/kernel.exe

# Make sure config.mk exists. This shouldn't be automated, so print an error.
config.mk:
	$(error Please copy config.mk.dist to config.mk and adjust it as needed)

# This rule is triggered by "include make/${TARGET}.mk" if TARGET is undefined.
# This shouldn't be automated, so print an error.
make/.mk:
	$(error TARGET is undefined. Set it on the command line or in config.mk)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${AS} ${ASFLAGS} -o $@ $<

%.exe: libs ${OBJFILES}
	@# The various ${$(call ...)} things expand in such a way that if
	@# this rule matches src/kernel.exe, it adds the following:
	@#   ${KERNEL_EXE_LDFLAGS} ${KERNEL_EXE_TARGETS}
	${LD} -o $@ -L src/libraries ${LDFLAGS} ${$(call rule_var,$@,LDFLAGS)} ${$(call rule_var,$@,TARGETS)} $(filter $*/%,$^) ${$(call rule_var,$@,LIBRARIES)}

%.a: ${OBJFILES}
	${AR} rc $@ $(filter $*/%,$^)
	${RANLIB} $@

# ASSUMPTION: Any library with a hyphen in the name are platform-specific.
#
# For each directory in src/libraries/ that does not include a hyphen, it
# includes that library. So, e.g., src/libraries/libc becomes
# src/libraries/libc.lib.
#
# For each directory that matches src/libraries/*-${TARGET}, it includes
# that library. (Using the same src/libraries/X -> src/libraries/X.lib rule
# as above.)
libs: $(shell find src/libraries -mindepth 1 -type d -not -name "*-*" -o -wholename "src/libraries/*-${TARGET}" -exec printf {}.a \;)

# Same deal as the "libs" target, but with modules.
modules: $(shell find src/modules -mindepth 1 -type d -not -name "*-*" -exec printf {}.exe \;) $(shell find src/modules -mindepth 1 -type d -wholename "src/modules/*-${TARGET}" -exec printf {}.exe \;)


iso: src/kernel.exe libs modules
	mkdir -p ${ISO_DIR}
	cp -r assets/isofs/ ./
	mkdir -p isofs/system isofs/libraries
	cp src/*.exe isofs/system
	cp src/libraries/*.a isofs/libraries
	genisoimage --boot-info-table -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o ${ISO_FILE} isofs

test: iso
	./bin/test.sh "${QEMU}"

qemu: iso
	${QEMU} -vga std -serial stdio -cdrom ${ISO_FILE}

qemu-monitor: iso
	${QEMU} -monitor stdio -cdrom ${ISO_FILE}

bochs: iso
	cd iso && ${BOCHS} -q -f bochsrc-${TARGET}.txt

vbox: iso
	VirtualBox --startvm ${NAME} --debug-statistics --debug-command-line --start-running

clean:
	@rm -rf ./isofs
	@find ./src -name '*.o'   -delete
	@find ./src -name '*.a'   -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete
	@find ./src -name '*.d'   -delete
	@rm -f ${ISO_FILE}

.PHONY: all iso libs modules clean test qemu qemu-monitor clean

# Don't auto-delete .o files.
.SECONDARY: ${OBJFILES}
