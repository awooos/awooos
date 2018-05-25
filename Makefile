NAME := awoo

BUILD_TYPE ?= debug

ISO_DIR  ?= iso/
ISO_FILE ?= ${ISO_DIR}/${NAME}${NAME_SUFFIX}-${TARGET}-${BUILD_TYPE}.iso

override C_INCLUDES += -I include -I src/libraries/dmm/include -I src/libraries/ali/include -I src/libraries/flail/include -I src/libraries/tinker/include -I src/libraries/hal/include

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2 -nostdinc -ffreestanding -fno-stack-protector -fno-builtin -fdiagnostics-show-option -Wall -Wextra -Wpedantic -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration ${C_INCLUDES}

override LDFLAGS += -nostdlib -g --whole-archive

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
AWOO_MAKE_CONFIG ?= config.mk
include ${AWOO_MAKE_CONFIG}
include make/${TARGET}.mk

QEMU    ?= qemu-system-${TARGET}

ifeq (${BUILD_TYPE},test)
# 1. Don't reboot on exit.
# 2. Add isa-debug-exit device, to allow to have qemu exit with a non-zero exit status.
#
# This combination allows us to do a clean shutdown and have qemu return a
# zero status code, or do a non-clean shutdown (using isa-debug-exit) and
# have qemu return a nonzero status code.
override QEMU_FLAGS += -no-reboot -device isa-debug-exit,iobase=0xf4,iosize=0x04
endif

KERNEL_EXE_LIBRARIES += -l :tests.a -l :tinker.a -l :flail.a -l :hal.a -l :dmm.a -l :ali.a -l :greeter.a -l :shell.a

ALL_FILES := $(wildcard            \
				src/libraries/*/src/*/     \
				src/libraries/*/src/*/*/   \
				src/libraries/*/platform-${TARGET}/*/    \
				src/libraries/*/platform-${TARGET}/*/*/  \
				src/kernel/*)
SRCFILES := $(filter %.c,${ALL_FILES}) $(filter %.asm,${ALL_FILES})
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, ${SRCFILES}))

BUILDINFO := $(shell mkdir -p include/awoo && ./bin/generate_build_info.sh ${BUILD_TYPE} ${TARGET} ${TEST_SECTION} > ./include/awoo/build_info.h)

# Any directory directly under src/libraries/ is treated as a library.
LIBRARIES := $(patsubst %/,%.a,$(filter %/,$(wildcard src/libraries/*/)))

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

src/kernel.exe: src/libraries/ali/src ${LIBRARIES}
	${LD} -o $@ -L src/libraries ${LDFLAGS} -T src/link-${TARGET}.ld src/kernel/start-${TARGET}.o src/kernel/main.o ${KERNEL_EXE_LIBRARIES}

%.a: ${OBJFILES}
	${AR} rcs $@ $(filter $*/%,$^)

iso: ${ISO_FILE}
${ISO_FILE}: src/kernel.exe
	cp -r assets/isofs/ ./
	cp src/kernel.exe isofs/
	${MKISOFS} -boot-info-table -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o ${ISO_FILE} isofs

test: lint
	$(MAKE) BUILD_TYPE=test qemu

lint:
	clang-check $(filter %.c,${SRCFILES}) -- ${C_INCLUDES}

qemu: iso
	${QEMU} ${QEMU_FLAGS} -vga std -serial stdio -cdrom ${ISO_FILE}

qemu-monitor: iso
	${QEMU} ${QEMU_FLAGS} -monitor stdio -cdrom ${ISO_FILE}

bochs: iso
	cd iso && ${BOCHS} -q -f bochsrc-${TARGET}.txt

vbox: iso
	VirtualBox --startvm ${NAME} --debug-statistics --debug-command-line --start-running

# Generate a nightly build.
nightly:
	$(MAKE) BUILD_TYPE=nightly NAME_SUFFIX="-$(shell date +'%Y-%m-%d')" iso

# Fetch all submodules.
src/libraries/%/src:
	@echo "Fetching submodules."
	git submodule update --quiet --recursive --init

# Update to the latest available versions of all submodules.
update-submodules:
	git submodule update --recursive --remote --init

clean:
	@rm -rf ./isofs ${ISO_DIR}*.iso ${OBJFILES} ${LIBRARIES} src/*.exe

.PHONY: all iso clean test qemu qemu-monitor clean fetch-submodules update-submodules

# Don't auto-delete .o files.
.SECONDARY: ${OBJFILES}
