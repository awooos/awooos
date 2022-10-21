FROM debian:11

ENV AWOO_MAKE_CONFIG="config.mk.dist"
ENV QEMU_FLAGS="-display none"
# ENV MAKEFLAGS="-j 2"

#RUN apk add --no-cache binutils clang lld git llvm5 make nasm qemu qemu-system-i386 syslinux xorriso
#RUN apk add --no-cache wget unzip

RUN apt-get update && apt-get install -y clang clang-tools lld git make nasm qemu qemu-system-x86 xorriso wget unzip
