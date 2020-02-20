FROM fedora:31

ENV AWOO_MAKE_CONFIG="config.mk.dist"
ENV QEMU_FLAGS="-display none"
ENV MAKEFLAGS="-j 2"

RUN dnf install -y clang make qemu qemu-system-x86 syslinux xorriso
