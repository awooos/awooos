# i686-specific targets and configuration.

BOOTSTRAP_TARGETS := src/bootstrap/i686/start.o
KERNEL_LDFLAGS    := -T src/bootstrap/i686/link.ld
