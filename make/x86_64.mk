# x86_64-specific targets and configuration.

# "The -mcmodel=large argument enables us to run the kernel at any 64-bit
#  virtual memory address we want. In fact, using the 'large' code model is
#  discouraged due to its inefficiency, but it can be fine as a start. Check
#  the SysV AMD64 ABI document for extra details."
#  — http://wiki.osdev.org/Creating_a_64-bit_kernel#Compiling
#
# -mno-red-zone: Disables the AMD64 ABI 128-byte "red zone", which resides
#                below the stack pointer. Without this, the kernel is
#                interrupt-unsafe.
# -mno-mmx: Disable SIMD instructions for now.
# -mno-sse -mno-sse2: Disable SSE floating-point operations because they
#                     need additional setup we are not currently doing.
#                     See also,
#                     http://wiki.osdev.org/Creating_a_64-bit_kernel#Compiling
override CFLAGS += -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2

# Tell everything we're doing an x86-64 build.
override CFLAGS  += -m64
override LDFLAGS += -melf_x86_64
override ASFLAGS += -felf64


# Add bootstrap/x86_64/start.o as a target for kernel.exe.
KERNEL_EXE_TARGETS := src/bootstrap/x86_64/start.o
# Have src/kernel.exe use the bootstrap linker script.
KERNEL_EXE_LDFLAGS := -T src/bootstrap/x86_64/link.ld


QEMU ?= qemu-system-x86_64
