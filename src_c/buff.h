#ifndef LISP16_BUFF_H
#define LISP16_BUFF_H

#include "mem.h"
#include "status.h"

#define LSP_BUFF_SIZE 32


typedef struct {
    lsp_mem_t *m;
    lsp_addr_t value;
    lsp_uint8_t buff[LSP_BUFF_SIZE];
    lsp_uint8_t buff_len;
} lsp_buff_t;


void lsp_buff_init(lsp_buff_t *b, lsp_mem_t *m);
lsp_status_t lsp_buff_push(lsp_buff_t *b, lsp_uint8_t c);
lsp_status_t lsp_buff_pop(lsp_buff_t *b, lsp_addr_t *value);
void lsp_buff_clear(lsp_buff_t *b);

#endif
