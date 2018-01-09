FROM alpine:edge

RUN apk add --no-cache python3 git

COPY bin/ /tmp/bin

ENTRYPOINT ["/tmp/bin/tinker.py"]
