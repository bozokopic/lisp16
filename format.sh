#!/bin/sh

set -e

cd $(dirname -- "$0")

SRC="$(find src_c -name '*.c' -o -name '*.h') $(find test_c -name '*.c')"

clang-format -style=file -i $SRC
