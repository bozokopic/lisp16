#!/bin/sh

set -e

cd $(dirname -- "$0")

CC=${CC:-gcc}
SRC="src_c/arch/posix.c $(find src_c -maxdepth 1 -name '*.c' -a ! -name 'main.c')"
OUT=build/test
ARCH=LSP_ARCH_POSIX
CFLAGS="-O2"

mkdir -p build/test

for i in test_c/*.c; do
    name=$(basename $i .c)
    $CC -DLSP_ARCH=$ARCH $CFLAGS -o $OUT/$name $SRC $i
    $OUT/$name
done
