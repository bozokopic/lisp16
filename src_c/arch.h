#ifndef LISP16_ARCH_H
#define LISP16_ARCH_H

#define LSP_ARCH_POSIX 0
#define LSP_ARCH_AVR8 1
#define LSP_ARCH_STM32 2

#ifndef LSP_ARCH
#error LSP_ARCH not defined
#endif

#if LSP_ARCH == LSP_ARCH_POSIX

#include <stdint.h>
typedef _Bool lsp_bool_t;
typedef int8_t lsp_int8_t;
typedef int16_t lsp_int16_t;
typedef int32_t lsp_int32_t;
typedef uint8_t lsp_uint8_t;
typedef uint16_t lsp_uint16_t;
typedef uint32_t lsp_uint32_t;

#elif LSP_ARCH == LSP_ARCH_AVR8

#include <stdint.h>
typedef _Bool lsp_bool_t;
typedef int8_t lsp_int8_t;
typedef int16_t lsp_int16_t;
typedef int32_t lsp_int32_t;
typedef uint8_t lsp_uint8_t;
typedef uint16_t lsp_uint16_t;
typedef uint32_t lsp_uint32_t;

#elif LSP_ARCH == LSP_ARCH_STM32

#include <stdint.h>
typedef _Bool lsp_bool_t;
typedef int8_t lsp_int8_t;
typedef int16_t lsp_int16_t;
typedef int32_t lsp_int32_t;
typedef uint8_t lsp_uint8_t;
typedef uint16_t lsp_uint16_t;
typedef uint32_t lsp_uint32_t;

#else

#error unknown LSP_ARCH

#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef true
#define true ((lsp_bool_t)1)
#endif

#ifndef false
#define false ((lsp_bool_t)0)
#endif

#endif
