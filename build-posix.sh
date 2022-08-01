#!/bin/sh

set -e

cd $(dirname -- "$0")

CC=${CC:-musl-gcc}
SRC="src_c/arch/posix.c src_c/*.c"
OUT=build/posix/lisp16
ARCH=LSP_ARCH_POSIX
CFLAGS="-O2"
# CFLAGS="-O0 -ggdb"

mkdir -p build/posix

$CC -DLSP_ARCH=$ARCH $CFLAGS -o $OUT -static $SRC
