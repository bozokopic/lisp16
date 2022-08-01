#!/bin/sh

set -e

cd $(dirname -- "$0")

MCU=atmega328p
FREQ=16000000UL
ARCH=LSP_ARCH_AVR8
CFLAGS="-Os"
SRC="src_c/arch/avr8.c src_c/*.c"
OUT_ELF=build/avr8/lisp16.elf
OUT_BIN=build/avr8/lisp16.bin

mkdir -p build/avr8

avr-gcc -mmcu=$MCU -DF_CPU=$FREQ -DLSP_ARCH=$ARCH $CFLAGS -o $OUT_ELF $SRC
avr-objcopy -O binary -j .text -j .data $OUT_ELF $OUT_BIN
