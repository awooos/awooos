FROM debian:10-slim

ENV AWOO_MAKE_CONFIG="config.mk.dist"
ENV QEMU_FLAGS="-display none"
ENV MAKEFLAGS="-j 2"
ENV CC=clang-6.0
ENV CLANG_CHECK=clang-check-6.0

RUN apt-get update && apt-get install -y clang-6.0 clang-tools-6.0 git make nasm qemu qemu-system-x86 xorriso
