# i686-specific targets and configuration.

# Add bootstrap/i686/start.o as a target for kernel.exe.
KERNEL_EXE_TARGETS := src/bootstrap/i686/start.o
# Have src/kernel.exe use the bootstrap linker script.
KERNEL_EXE_LDFLAGS := -T src/bootstrap/i686/link.ld
