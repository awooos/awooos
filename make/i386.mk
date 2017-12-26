# i386-specific targets and configuration.

# Tell everything we're doing an i386 build.
override CFLAGS  += -m32
override LDFLAGS += -melf_i386
override ASFLAGS += -felf32

# i386-specific external libraries.
override CFLAGS += -I src/libraries/dux-mm-i386/include

KERNEL_EXE_LIBRARIES_APPEND := -l :dux-mm-i386.a

QEMU ?= qemu-system-i386
