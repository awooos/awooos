#!/bin/sh

if [ "`uname -m`" = "amd64" ]; then
    echo "x86_64"
else
    uname -m
fi
