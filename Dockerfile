FROM alpine:3.6

ENV AWOO_MAKE_CONFIG config.mk.dist

RUN apk add --no-cache binutils clang nasm make xorriso git

ENTRYPOINT ["make"]

