#ifndef LISP16_ARCH_AVR8_H
#define LISP16_ARCH_AVR8_H

#include "../mem.h"
#include "../stream.h"

#define LSP_ARCH_INIT lsp_arch_avr8_init

#define LSP_ARCH_CREATE_MEM lsp_arch_avr8_create_mem
#define LSP_ARCH_FREE_MEM lsp_arch_avr8_free_mem

#define LSP_ARCH_CREATE_IN_STREAM lsp_arch_avr8_create_in_stream
#define LSP_ARCH_FREE_IN_STREAM lsp_arch_avr8_free_in_stream

#define LSP_ARCH_CREATE_OUT_STREAM lsp_arch_avr8_create_out_stream
#define LSP_ARCH_FREE_OUT_STREAM lsp_arch_avr8_free_out_stream


void lsp_arch_avr8_init();

lsp_mem_t *lsp_arch_avr8_create_mem();
void lsp_arch_avr8_free_mem(lsp_mem_t *m);

lsp_in_stream_t *lsp_arch_avr8_create_in_stream();
void lsp_arch_avr8_free_in_stream(lsp_in_stream_t *s);

lsp_out_stream_t *lsp_arch_avr8_create_out_stream();
void lsp_arch_avr8_free_out_stream(lsp_out_stream_t *s);

#endif
