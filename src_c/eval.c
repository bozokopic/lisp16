#include "eval.h"
#include "ctx.h"
#include "apply.h"


static lsp_status_t eval_args(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args,
                              lsp_addr_t *result) {
    lsp_addr_t last = e->m->nil;
    *result = e->m->nil;
    lsp_status_t status;

    while (args != e->m->nil) {
        lsp_addr_t arg = lsp_mem_get_pair_first(e->m, args);
        status = lsp_env_resolve(e, ctx, arg, &arg);
        if (status != LSP_SUCCESS)
            goto error;

        lsp_addr_t new_last;
        status = lsp_mem_create_pair(e->m, arg, e->m->nil, &new_last);
        lsp_mem_dec_ref(e->m, arg);
        if (status != LSP_SUCCESS)
            goto error;

        if (*result == e->m->nil) {
            *result = new_last;

        } else {
            lsp_mem_set_pair_second(e->m, last, new_last);
            lsp_mem_dec_ref(e->m, new_last);
        }

        last = new_last;
        args = lsp_mem_get_pair_second(e->m, args);
    }

    return LSP_SUCCESS;

error:
    lsp_mem_dec_ref(e->m, *result);
    return status;
}


lsp_status_t lsp_eval(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t value) {
    lsp_status_t status = LSP_SUCCESS;

    if (lsp_mem_is_number(e->m, value) || lsp_mem_is_string(e->m, value) ||
        lsp_mem_is_builtin(e->m, value) ||
        lsp_mem_is_function_or_syntax(e->m, value))
        return lsp_env_set_result_value(e, value);

    if (lsp_mem_is_symbol(e->m, value)) {
        lsp_addr_t result;
        status = lsp_ctx_get(e->m, ctx, value, &result);
        if (status != LSP_SUCCESS)
            return status;

        status = lsp_env_set_result_value(e, result);
        lsp_mem_dec_ref(e->m, result);
        return status;
    }

    if (lsp_mem_is_pair(e->m, value)) {
        if (value == e->m->nil)
            return lsp_env_set_result_value(e, e->m->nil);

        lsp_addr_t callable = lsp_mem_get_pair_first(e->m, value);
        lsp_addr_t args = lsp_mem_get_pair_second(e->m, value);

        status = lsp_env_resolve(e, ctx, callable, &callable);
        if (status != LSP_SUCCESS)
            return status;

        if (lsp_mem_is_builtin_function(e->m, callable) ||
            lsp_mem_is_function(e->m, callable)) {
            status = eval_args(e, ctx, args, &args);
        } else {
            status = lsp_mem_inc_ref(e->m, args);
        }
        if (status != LSP_SUCCESS) {
            lsp_mem_dec_ref(e->m, callable);
            return status;
        }

        status = lsp_apply(e, ctx, callable, args);
        lsp_mem_dec_ref(e->m, callable);
        lsp_mem_dec_ref(e->m, args);
        return status;
    }

    return LSP_ERR_EVAL;
}
