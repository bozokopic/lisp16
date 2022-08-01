#ifndef LISP16_CTX_H
#define LISP16_CTX_H

#include "mem.h"


lsp_status_t lsp_ctx_create(lsp_mem_t *m, lsp_addr_t *ctx);
lsp_status_t lsp_ctx_copy(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t *result);
lsp_status_t lsp_ctx_add(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t symbol,
                         lsp_addr_t value);
lsp_status_t lsp_ctx_set(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t symbol,
                         lsp_addr_t value);
lsp_status_t lsp_ctx_get(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t symbol,
                         lsp_addr_t *value);

#endif
