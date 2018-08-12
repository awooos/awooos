NAME := awoo

BUILD_TYPE ?= debug

ISO_DIR  ?= iso/
ISO_FILE ?= ${ISO_DIR}/${NAME}${NAME_SUFFIX}-${TARGET}-${BUILD_TYPE}.iso

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2 -nostdinc     \
					-ffreestanding -fno-stack-protector -fno-builtin \
					-fdiagnostics-show-option -Werror -Weverything   \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla

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

QEMU ?= qemu-system-${TARGET}

ifeq (${BUILD_TYPE},test)
# 1. Don't reboot on exit.
# 2. Add isa-debug-exit device, to allow to have qemu exit with a non-zero exit status.
#
# This combination allows us to do a clean shutdown and have qemu return a
# zero status code, or do a non-clean shutdown (using isa-debug-exit) and
# have qemu return a nonzero status code.
override QEMU_FLAGS += -no-reboot -device isa-debug-exit,iobase=0xf4,iosize=0x04
endif

C_INCLUDES := -I include $(patsubst %,-I %,$(wildcard src/libraries/*/include))

KERNEL_LDFLAGS := $(patsubst src/libraries/%/,-l :%.a,$(filter %/,$(wildcard src/libraries/*/)))

ALL_FILES := $(wildcard            \
				src/libraries/*/src/*/     \
				src/libraries/*/src/*/*/   \
				src/libraries/*/platform-${TARGET}/*/    \
				src/libraries/*/platform-${TARGET}/*/*/  \
				src/kernel/*)
SRCFILES := $(filter %.c,${ALL_FILES}) $(filter %.asm,${ALL_FILES})
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, ${SRCFILES}))

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

generated_headers:
	mkdir -p include/awoo
	./bin/generate_build_info.sh ${BUILD_TYPE} ${TARGET} > ./include/awoo/build_info.h

%.o: %.c generated_headers
	${CC} ${CFLAGS} ${C_INCLUDES} -c $< -o $@

%.o: %.asm
	${AS} ${ASFLAGS} -o $@ $<

src/kernel.exe: ${LIBRARIES}
	${LD} -o $@ -L src/libraries ${LDFLAGS} -T src/link-${TARGET}.ld src/kernel/start-${TARGET}.o src/kernel/main.o ${KERNEL_LDFLAGS}

%.a: ${OBJFILES}
	${AR} rcs $@ $(filter $*/%,$^)

iso: ${ISO_FILE}
${ISO_FILE}: src/kernel.exe
	@cp -r assets/isofs/ ./
	@cp src/kernel.exe isofs/
	xorriso -report_about HINT -abort_on WARNING -as mkisofs -quiet -boot-info-table -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o ${ISO_FILE} isofs

test: lint
	@$(MAKE) BUILD_TYPE=test qemu

lint: generated_headers
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
fetch-submodules:
	git submodule update --recursive --init

# Update to the latest available versions of all submodules.
update-submodules:
	git submodule update --recursive --remote --init

# List all of the event_trigger() and event_watch() calls.
list-events:
	@grep -rEho '(event_trigger|event_watch)\(".*"' src | tr '("' '\t ' | sort

clean:
	@rm -rf ./isofs ${ISO_DIR}*.iso ${OBJFILES} ${LIBRARIES} src/*.exe

.PHONY: all iso clean test qemu qemu-monitor clean fetch-submodules update-submodules generated_headers

# Don't auto-delete .o files.
.SECONDARY: ${OBJFILES}
