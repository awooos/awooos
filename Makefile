NAME := awoo

BUILD_TYPE ?= debug

ISO_DIR  ?= iso/
ISO_FILE ?= ${ISO_DIR}/${NAME}${NAME_SUFFIX}-${TARGET}-${BUILD_TYPE}.iso

override C_INCLUDES += -I include -I src/libraries/dmm-${TARGET}/include -I src/libraries/ali/include -I src/libraries/flail/include

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2 -nostdinc -ffreestanding -fno-stack-protector -fno-builtin -fdiagnostics-show-option -Wall -Wextra -Wpedantic -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration ${C_INCLUDES} -DDMM_INTRUSIVE

override LDFLAGS += -nostdlib -g

override ASFLAGS +=

# If config.mk doesn't exist, it triggers the corresponding rule.
# If ${TARGET} is undefined, this triggers the "make/.mk" rule.
#
# Also, the LAST INCLUDED FILE is included first, because... reasons?
#
# Given that and config.mk needing to be loaded after ${TARGET}.mk,
# (to allow config.mk to override defaults), we include it _before_
# ${TARGET}.mk, so it's loaded afterwards.
# 
# I hate Make so much.
include make/despair.mk
AWOO_MAKE_CONFIG ?= config.mk
include ${AWOO_MAKE_CONFIG}
include make/${TARGET}.mk

ifeq (${BUILD_TYPE},test)
# 1. Don't reboot on exit.
# 2. Add isa-debug-exit device, to allow to have qemu exit with a non-zero exit status.
#
# This combination allows us to do a clean shutdown and have qemu return a
# zero status code, or do a non-clean shutdown (using isa-debug-exit) and
# have qemu return a nonzero status code.
override QEMU_FLAGS += -no-reboot -device isa-debug-exit,iobase=0xf4,iosize=0x04
endif

# Have src/kernel.exe use the target-specific linker script.
KERNEL_EXE_LDFLAGS := -T src/link-${TARGET}.ld
# Have src/kernel.exe link to the various libraries necessary.
KERNEL_EXE_LIBRARIES += -l :bootstrap-${TARGET}.a -l :tests.a -l :ktest.a -l :eventually.a -l :flail.a -l :hal-${TARGET}.a -l :dmm-${TARGET}.a -l :flail.a -l :scheduler.a -l :ali.a -l :greeter.a


KERNEL_EXE_LIBRARIES += ${KERNEL_EXE_LIBRARIES_APPEND}

# == Begin gross bullshit for only matching things for the current platform. ==

# We're searching for .c and .asm files.
SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'

# Ignore things that are target-specific.
EXCLUDE_ALL_TARGET_DIRECTORIES := '(' '!' -wholename 'src/*/*-*/*' ')'

# src/libraries/bootstrap-${TARGET}, src/libraries/hal-${TARGET}, etc.
INCLUDE_CURRENT_TARGET_DIRECTORIES := '(' -wholename 'src/*/*-${TARGET}/*' ')'

# == End gross bullshit for only matching things for the current platform.   ==

SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES} '(' ${EXCLUDE_ALL_TARGET_DIRECTORIES} -o ${INCLUDE_CURRENT_TARGET_DIRECTORIES} ')')
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, ${SRCFILES}))

BUILDINFO := $(shell ./bin/generate_build_info.sh ${BUILD_TYPE} ${TARGET} ${TEST_SECTION} > ./include/awoo/build_info.h)

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

%.exe: libraries ${OBJFILES}
	@# The various ${$(call ...)} things expand in such a way that if
	@# this rule matches src/kernel.exe, it adds the following:
	@#   ${KERNEL_EXE_LDFLAGS} ${KERNEL_EXE_TARGETS}
	${LD} -o $@ -L src/modules -L src/libraries ${LDFLAGS} ${$(call rule_var,$@,LDFLAGS)} ${$(call rule_var,$@,TARGETS)} $(filter $*/%,$^) ${$(call rule_var,$@,LIBRARIES)}

%.a: ${OBJFILES}
	${AR} rc $@ $(filter $*/%,$^)
	${RANLIB} $@

# Any directory directly under src/libraries/ is treated as a library.
libraries: $(shell find src/libraries -mindepth 1 -type d -exec printf "{}.a " \;)
#libraries: generic_libraries target_libraries

#generic_libraries: $(shell find src/libraries -mindepth 1 -type d -not -name "*-*" -exec printf "{}.a " \;)
#target_libraries: $(shell find src/libraries -mindepth 1 -type d -wholename "src/libraries/*-${TARGET}" -exec printf "{}.a " \;)

# ASSUMPTION: Any module with a hyphen in the name are platform-specific.
#
# For each directory in src/modules/ that does not include a hyphen, it
# includes that module. So, e.g., src/modules/libc becomes
# src/modules/libc.a.
#
# For each directory that matches src/modules/*-${TARGET}, it includes
# that module.
# (Using the same src/modules/X -> src/modules/X.a rule as above.)
#modules: $(shell find src/modules -mindepth 1 -type d -not -name "*-*" -exec printf {}.exe\  \;) $(shell find src/modules -mindepth 1 -type d -wholename "src/modules/*-${TARGET}" -exec printf {}.a\  \;)


iso: src/kernel.exe libraries
	mkdir -p ${ISO_DIR}
	cp -r assets/isofs/ ./
	mkdir -p isofs/system isofs/libraries
	cp src/*.exe isofs/system
	cp src/libraries/*.a isofs/libraries
	${MKISOFS} -boot-info-table -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o ${ISO_FILE} isofs

test--%:
	$(MAKE) BUILD_TYPE=test TEST_SECTION=$* clean qemu

test-general: test--1
test-panic: test--2

test-lint:
	clang-check $(shell find -name '*.c') -- ${C_INCLUDES}
lint: test-lint

test: test-general test-panic

qemu: iso
	${QEMU} ${QEMU_FLAGS} -vga std -serial stdio -cdrom ${ISO_FILE}

qemu-monitor: iso
	${QEMU} ${QEMU_FLAGS} -monitor stdio -cdrom ${ISO_FILE}

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
	@find ./iso -name '*.iso' -delete

.PHONY: all iso libraries modules clean test qemu qemu-monitor clean dockerhub-release

# Don't auto-delete .o files.
.SECONDARY: ${OBJFILES}
