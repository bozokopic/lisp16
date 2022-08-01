#include "env.h"
#include "ctx.h"
#include "eval.h"


static void init_result(lsp_env_t *e) {
    e->result.is_value = true;
    e->result.ctx = e->m->nil;
    e->result.value = e->m->nil;
}


static void release_result(lsp_env_t *e) {
    lsp_mem_dec_ref(e->m, e->result.ctx);
    lsp_mem_dec_ref(e->m, e->result.value);

    init_result(e);
}


void lsp_env_init(lsp_env_t *e, lsp_mem_t *m, lsp_in_stream_t *in,
                  lsp_out_stream_t *out) {
    e->m = m;
    e->in = in;
    e->out = out;

    init_result(e);
}


lsp_status_t lsp_env_set_result_value(lsp_env_t *e, lsp_addr_t value) {
    release_result(e);

    lsp_status_t status = lsp_mem_inc_ref(e->m, value);
    if (status != LSP_SUCCESS)
        return status;

    e->result.is_value = true;
    e->result.value = value;
    return LSP_SUCCESS;
}


lsp_status_t lsp_env_set_result_eval(lsp_env_t *e, lsp_addr_t ctx,
                                     lsp_addr_t value) {
    release_result(e);

    lsp_status_t status = lsp_mem_inc_ref(e->m, ctx);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_mem_inc_ref(e->m, value);
    if (status != LSP_SUCCESS) {
        lsp_mem_dec_ref(e->m, ctx);
        return status;
    }

    e->result.is_value = false;
    e->result.ctx = ctx;
    e->result.value = value;
    return LSP_SUCCESS;
}


lsp_status_t lsp_env_resolve(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t value,
                             lsp_addr_t *result) {
    lsp_status_t status = lsp_env_set_result_eval(e, ctx, value);
    if (status != LSP_SUCCESS)
        return status;

    while (!e->result.is_value) {
        lsp_addr_t eval_ctx = e->result.ctx;
        lsp_addr_t eval_value = e->result.value;
        init_result(e);

        status = lsp_eval(e, eval_ctx, eval_value);
        lsp_mem_dec_ref(e->m, eval_ctx);
        lsp_mem_dec_ref(e->m, eval_value);
        if (status != LSP_SUCCESS)
            return status;
    }

    *result = e->result.value;
    init_result(e);
    return LSP_SUCCESS;
}
