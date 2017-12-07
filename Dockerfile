FROM alpine:edge

ENV AWOO_MAKE_CONFIG config.mk.dist
ENV QEMU_FLAGS -display none

RUN apk add --no-cache binutils clang nasm make xorriso git qemu qemu-system-i386

ENTRYPOINT ["make"]
