# i386-specific targets and configuration.

# Tell everything we're doing an i386 build.
override CFLAGS  += -m32
override LDFLAGS += -melf_i386
override ASFLAGS += -felf32

# i386-specific external libraries.
override CFLAGS += -I src/libraries/dmm-i386/include

QEMU ?= qemu-system-i386
