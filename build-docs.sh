#!/bin/sh

set -e

cd $(dirname -- "$0")

PYTHON=${PYTHON:-python3}
SRC=docs
DST=build/docs

mkdir -p $DST
$PYTHON -m sphinx -q -b html $SRC $DST
