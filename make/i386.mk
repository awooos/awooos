# i386-specific targets and configuration.

# Tell everything we're doing an i386 build.
override CFLAGS  += -m32
override LDFLAGS += -melf_i386
override ASFLAGS += -felf32

# Add bootstrap/i386/start.o as a target for kernel.exe.
KERNEL_EXE_TARGETS := src/bootstrap/i386/start.o
# Have src/kernel.exe use the bootstrap linker script.
KERNEL_EXE_LDFLAGS := -T src/bootstrap/i386/link.ld

QEMU ?= qemu-system-i386
