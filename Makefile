NAME := awoo

BUILD_TYPE ?= debug

TARGET ?= i686

ISO_DIR  ?= iso/
ISO_FILE ?= ${ISO_DIR}/${NAME}-${TARGET}.iso

override CFLAGS += -std=c11 -pedantic-errors -gdwarf-2 -m32 -nostdinc -ffreestanding -fno-stack-protector -fno-builtin -fdiagnostics-show-option -Wall -Wextra -Wpedantic -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration

override LDFLAGS += -nostdlib -g -melf_i386

override ASFLAGS += -felf32

include config.mk
include make/${TARGET}.mk

SRCFILES := $(shell find 'src' '(' -name '*.c' -o -name '*.asm' ')')
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, ${SRCFILES}))

BUILDINFO := $(shell ./bin/buildinfo.sh ${BUILD_TYPE} ${TARGET} > ./include/buildinfo.h)

all: config.mk src/kernel.exe

config.mk:
	@printf "You will need to copy config.mk.dist to config.mk first.\n"
	@false

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${AS} ${ASFLAGS} -o $@ $<

%.exe: libs ${OBJFILES}
	${LD} -o $@ ${LDFLAGS} $(filter $*/%,$^) -L src/libraries

%.lib: ${OBJFILES}
	${AR} rc $@ $(filter $*/%,$^)
	${RANLIB} $@

src/kernel.exe: ${BOOTSTRAP_TARGETS} libs modules $(filter %,${OBJFILES})
	${LD} -o $@ ${LDFLAGS} ${KERNEL_LDFLAGS} $(filter src/bootstrap/% src/kernel/%,$^) -L src/libraries

# ASSUMPTION: Any library with a hyphen in the name are platform-specific.
#
# For each directory in src/libraries/ that does not include a hyphen, it
# includes that library. So, e.g., src/libraries/libc becomes
# src/libraries/libc.lib.
#
# For each directory that matches src/libraries/*-${TARGET}, it includes
# that library. (Using the same src/libraries/X -> src/libraries/X.lib rule
# as above.)
libs: $(shell find src/libraries -mindepth 1 -type d -not -name "*-*" -exec printf {}.lib \;) $(shell find src/libraries -mindepth 1 -type d -wholename "src/libraries/*-${TARGET}" -exec printf {}.lib \;)

# Same deal as the "libs" target, but with modules.
modules: $(shell find src/modules -mindepth 1 -type d -not -name "*-*" -exec printf {}.exe \;) $(shell find src/modules -mindepth 1 -type d -wholename "src/modules/*-${TARGET}" -exec printf {}.exe \;)


iso: src/kernel.exe libs modules
	mkdir -p ${ISO_DIR}
	cp -r data/isofs/ isofs/
	mkdir -p isofs/system isofs/libraries
	cp src/*.exe isofs/system
	cp src/libraries/*.lib isofs/libraries
	genisoimage --boot-info-table -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o ${ISO_FILE} isofs

test: iso
	./bin/test.sh "${QEMU}"

qemu: iso
	${QEMU} -vga std -serial stdio -cdrom ${ISO_FILE}

qemu-monitor: iso
	${QEMU} -monitor stdio -cdrom ${ISO_FILE}

vbox: iso
	VirtualBox --startvm ${NAME} --debug-statistics --debug-command-line --start-running

clean:
	@rm -rf ./isofs
	@find ./src -name '*.o'   -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete
	@find ./src -name '*.d'   -delete
	@rm -f ${ISO_FILE}

.PHONY: all iso libs modules clean test qemu qemu-monitor clean

# Don't auto-delete .o files.
.SECONDARY: ${OBJFILES}
