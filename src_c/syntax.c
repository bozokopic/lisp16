#include "syntax.h"
#include "ctx.h"
#include "eval.h"


lsp_builtin_entry_t lsp_syntaxes[] = {
    {"lambda", lsp_syntax_lambda}, {"syntax", lsp_syntax_syntax},
    {"define", lsp_syntax_define}, {"set!", lsp_syntax_set},
    {"begin", lsp_syntax_begin},   {"quote", lsp_syntax_quote},
    {"if", lsp_syntax_if},         {NULL, NULL}};


lsp_status_t lsp_syntax_lambda(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    if (args == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t fn_args = lsp_mem_get_pair_first(e->m, args);
    lsp_addr_t fn_body = lsp_mem_get_pair_second(e->m, args);

    if (!lsp_mem_is_symbol(e->m, fn_args) && !lsp_mem_is_pair(e->m, fn_args))
        return LSP_ERR_ARG_TYPE;

    if (fn_body == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t ctx_copy;
    lsp_status_t status = lsp_ctx_copy(e->m, ctx, &ctx_copy);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t result;
    status = lsp_mem_create_function(e->m, ctx_copy, fn_args, fn_body, &result);
    lsp_mem_dec_ref(e->m, ctx_copy);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_syntax_syntax(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    if (args == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t syntax_args = lsp_mem_get_pair_first(e->m, args);
    lsp_addr_t syntax_body = lsp_mem_get_pair_second(e->m, args);

    if (!lsp_mem_is_symbol(e->m, syntax_args) &&
        !lsp_mem_is_pair(e->m, syntax_args))
        return LSP_ERR_ARG_TYPE;

    if (syntax_body == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t ctx_copy;
    lsp_status_t status = lsp_ctx_copy(e->m, ctx, &ctx_copy);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t result;
    status = lsp_mem_create_syntax(e->m, ctx_copy, syntax_args, syntax_body,
                                   &result);
    lsp_mem_dec_ref(e->m, ctx_copy);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_syntax_define(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t symbol;
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &symbol, &value);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_symbol(e->m, symbol))
        return LSP_ERR_ARG_TYPE;

    status = lsp_env_resolve(e, ctx, value, &value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_ctx_add(e->m, ctx, symbol, value);
    lsp_mem_dec_ref(e->m, value);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_env_set_result_value(e, e->m->nil);
}


lsp_status_t lsp_syntax_set(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t symbol;
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &symbol, &value);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_symbol(e->m, symbol))
        return LSP_ERR_ARG_TYPE;

    status = lsp_env_resolve(e, ctx, value, &value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_ctx_set(e->m, ctx, symbol, value);
    lsp_mem_dec_ref(e->m, value);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_env_set_result_value(e, e->m->nil);
}


lsp_status_t lsp_syntax_begin(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    if (args == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    while (true) {
        lsp_addr_t value = lsp_mem_get_pair_first(e->m, args);
        lsp_addr_t next_args = lsp_mem_get_pair_second(e->m, args);

        if (next_args == e->m->nil)
            return lsp_env_set_result_eval(e, ctx, value);

        lsp_status_t status = lsp_env_resolve(e, ctx, value, &value);
        if (status != LSP_SUCCESS)
            return status;

        lsp_mem_dec_ref(e->m, value);
        args = next_args;
    }
}


lsp_status_t lsp_syntax_quote(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_env_set_result_value(e, value);
}


lsp_status_t lsp_syntax_if(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    if (args == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t test = lsp_mem_get_pair_first(e->m, args);

    args = lsp_mem_get_pair_second(e->m, args);
    if (args == e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t true_value = lsp_mem_get_pair_first(e->m, args);

    lsp_addr_t false_value;
    args = lsp_mem_get_pair_second(e->m, args);
    if (args == e->m->nil) {
        false_value = e->m->nil;

    } else {
        false_value = lsp_mem_get_pair_first(e->m, args);
        args = lsp_mem_get_pair_second(e->m, args);
    }

    if (args != e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_status_t status = lsp_env_resolve(e, ctx, test, &test);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_false = (lsp_mem_is_number(e->m, test) &&
                           lsp_mem_get_number(e->m, test) == 0) ||
                          (lsp_mem_is_pair(e->m, test) && test == e->m->nil) ||
                          (lsp_mem_is_string(e->m, test) &&
                           lsp_mem_get_string_len(e->m, test) == 0) ||
                          (lsp_mem_is_symbol(e->m, test) &&
                           lsp_mem_get_symbol_len(e->m, test) == 0);
    lsp_mem_dec_ref(e->m, test);

    return lsp_env_set_result_eval(e, ctx,
                                   (is_false ? false_value : true_value));
}
