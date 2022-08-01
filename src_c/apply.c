#include "apply.h"
#include "ctx.h"
#include "eval.h"
#include "function.h"
#include "syntax.h"
#include "write.h"


static lsp_status_t create_ctx(lsp_env_t *e, lsp_addr_t parent_ctx,
                               lsp_addr_t arg_names, lsp_addr_t arg_values,
                               lsp_addr_t *result) {
    lsp_status_t status = lsp_ctx_copy(e->m, parent_ctx, result);
    if (status != LSP_SUCCESS)
        return status;

    while (arg_names != e->m->nil) {
        if (lsp_mem_is_symbol(e->m, arg_names)) {
            status = lsp_ctx_add(e->m, *result, arg_names, arg_values);
            arg_values = e->m->nil;
            break;
        }

        if (arg_values == e->m->nil) {
            status = LSP_ERR_ARG_COUNT;
            break;
        }

        lsp_addr_t arg_name = lsp_mem_get_pair_first(e->m, arg_names);
        lsp_addr_t arg_value = lsp_mem_get_pair_first(e->m, arg_values);

        if (!lsp_mem_is_symbol(e->m, arg_name)) {
            status = LSP_ERR_ARG_TYPE;
            break;
        }

        status = lsp_ctx_add(e->m, *result, arg_name, arg_value);
        if (status != LSP_SUCCESS)
            break;

        arg_names = lsp_mem_get_pair_second(e->m, arg_names);
        arg_values = lsp_mem_get_pair_second(e->m, arg_values);
    }

    if (status == LSP_SUCCESS && arg_values != e->m->nil)
        status = LSP_ERR_ARG_COUNT;

    if (status != LSP_SUCCESS)
        lsp_mem_dec_ref(e->m, *result);

    return status;
}


static lsp_status_t apply_builtin_function(lsp_env_t *e, lsp_addr_t ctx,
                                           lsp_addr_t callable,
                                           lsp_addr_t args) {
    lsp_uint16_t index = lsp_mem_get_builtin_index(e->m, callable);
    lsp_builtin_cb_t cb = lsp_functions[index].cb;
    return cb(e, ctx, args);
}


static lsp_status_t apply_builtin_syntax(lsp_env_t *e, lsp_addr_t ctx,
                                         lsp_addr_t callable, lsp_addr_t args) {
    lsp_uint16_t index = lsp_mem_get_builtin_index(e->m, callable);
    lsp_builtin_cb_t cb = lsp_syntaxes[index].cb;
    return cb(e, ctx, args);
}


static lsp_status_t apply_function(lsp_env_t *e, lsp_addr_t ctx,
                                   lsp_addr_t callable, lsp_addr_t args) {
    lsp_addr_t parent_ctx = lsp_mem_get_function_parent_ctx(e->m, callable);
    lsp_addr_t arg_names = lsp_mem_get_function_args(e->m, callable);
    lsp_addr_t body = lsp_mem_get_function_body(e->m, callable);

    lsp_addr_t fn_ctx;
    lsp_status_t status = create_ctx(e, parent_ctx, arg_names, args, &fn_ctx);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_syntax_begin(e, fn_ctx, body);
    lsp_mem_dec_ref(e->m, fn_ctx);
    return status;
}


static lsp_status_t apply_syntax(lsp_env_t *e, lsp_addr_t ctx,
                                 lsp_addr_t callable, lsp_addr_t args) {
    lsp_addr_t parent_ctx = lsp_mem_get_syntax_parent_ctx(e->m, callable);
    lsp_addr_t arg_names = lsp_mem_get_syntax_args(e->m, callable);
    lsp_addr_t body = lsp_mem_get_syntax_body(e->m, callable);

    lsp_addr_t syntax_ctx;
    lsp_status_t status =
        create_ctx(e, parent_ctx, arg_names, args, &syntax_ctx);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t result = e->m->nil;
    while (body != e->m->nil) {
        lsp_mem_dec_ref(e->m, result);

        lsp_addr_t value = lsp_mem_get_pair_first(e->m, body);
        status = lsp_env_resolve(e, syntax_ctx, value, &result);
        if (status != LSP_SUCCESS)
            break;

        body = lsp_mem_get_pair_second(e->m, body);
    }

    lsp_mem_dec_ref(e->m, syntax_ctx);
    if (status != LSP_SUCCESS)
        return status;

    // lsp_write(e->m, e->out, result);
    // lsp_out_stream_write(e->out, '\n');

    status = lsp_env_set_result_eval(e, ctx, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_apply(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t callable,
                       lsp_addr_t args) {
    if (lsp_mem_is_builtin_function(e->m, callable))
        return apply_builtin_function(e, ctx, callable, args);

    if (lsp_mem_is_builtin_syntax(e->m, callable))
        return apply_builtin_syntax(e, ctx, callable, args);

    if (lsp_mem_is_function(e->m, callable))
        return apply_function(e, ctx, callable, args);

    if (lsp_mem_is_syntax(e->m, callable))
        return apply_syntax(e, ctx, callable, args);

    return LSP_ERR_APPLY;
}
