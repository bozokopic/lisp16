#ifndef LISP16_ENV_H
#define LISP16_ENV_H

#include "mem.h"
#include "stream.h"


typedef struct {
    lsp_mem_t *m;
    lsp_in_stream_t *in;
    lsp_out_stream_t *out;

    // internal
    struct {
        lsp_bool_t is_value;
        lsp_addr_t ctx;
        lsp_addr_t value;
    } result;
} lsp_env_t;


void lsp_env_init(lsp_env_t *e, lsp_mem_t *m, lsp_in_stream_t *in,
                  lsp_out_stream_t *out);
lsp_status_t lsp_env_set_result_value(lsp_env_t *e, lsp_addr_t value);
lsp_status_t lsp_env_set_result_eval(lsp_env_t *e, lsp_addr_t ctx,
                                     lsp_addr_t value);
lsp_status_t lsp_env_resolve(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t value,
                             lsp_addr_t *result);

#endif
