#include "ctx.h"
#include "function.h"
#include "syntax.h"


static lsp_bool_t contains_symbol(lsp_mem_t *m, lsp_addr_t ctx,
                                  lsp_addr_t symbol) {
    while (ctx != m->nil) {
        lsp_addr_t entry = lsp_mem_get_pair_first(m, ctx);
        lsp_addr_t entry_symbol = lsp_mem_get_pair_first(m, entry);

        if (lsp_mem_eq(m, entry_symbol, symbol))
            return true;

        ctx = lsp_mem_get_pair_second(m, ctx);
    }

    return false;
}


static lsp_status_t remove_symbol(lsp_mem_t *m, lsp_addr_t ctx,
                                  lsp_addr_t symbol) {
    lsp_addr_t list = lsp_mem_get_pair_first(m, ctx);

    lsp_addr_t result = m->nil;
    lsp_addr_t result_last = m->nil;
    lsp_status_t status = LSP_SUCCESS;

    while (list != m->nil) {
        lsp_addr_t entry = lsp_mem_get_pair_first(m, list);
        lsp_addr_t entry_symbol = lsp_mem_get_pair_first(m, entry);
        list = lsp_mem_get_pair_second(m, list);

        if (lsp_mem_eq(m, entry_symbol, symbol)) {
            if (result == m->nil) {
                result = list;
                status = lsp_mem_inc_ref(m, list);

            } else {
                lsp_mem_set_pair_second(m, result_last, list);
            }

            break;
        }

        lsp_addr_t new_result_last;
        status = lsp_mem_create_pair(m, entry, m->nil, &new_result_last);
        if (status != LSP_SUCCESS)
            break;

        if (result == m->nil) {
            result = new_result_last;

        } else {
            lsp_mem_set_pair_second(m, result_last, new_result_last);
            lsp_mem_dec_ref(m, new_result_last);
        }

        result_last = new_result_last;
    }

    if (status == LSP_SUCCESS)
        lsp_mem_set_pair_first(m, ctx, result);

    lsp_mem_dec_ref(m, result);
    return status;
}


lsp_status_t lsp_ctx_create(lsp_mem_t *m, lsp_addr_t *ctx) {
    lsp_addr_t list = m->nil;
    lsp_addr_t list_last = m->nil;
    lsp_status_t status = LSP_SUCCESS;

    for (uint8_t i = 0; status == LSP_SUCCESS && lsp_syntaxes[i].name; ++i) {
        lsp_addr_t symbol;
        status =
            lsp_mem_create_symbol_from_char(m, lsp_syntaxes[i].name, &symbol);
        if (status != LSP_SUCCESS)
            break;

        lsp_addr_t value;
        status = lsp_mem_create_builtin_syntax(m, i, &value);
        if (status != LSP_SUCCESS) {
            lsp_mem_dec_ref(m, symbol);
            break;
        }

        lsp_addr_t entry;
        status = lsp_mem_create_pair(m, symbol, value, &entry);
        lsp_mem_dec_ref(m, symbol);
        lsp_mem_dec_ref(m, value);
        if (status != LSP_SUCCESS)
            break;

        lsp_addr_t new_list_last;
        status = lsp_mem_create_pair(m, entry, m->nil, &new_list_last);
        lsp_mem_dec_ref(m, entry);
        if (status != LSP_SUCCESS)
            break;

        if (list == m->nil) {
            list = new_list_last;

        } else {
            lsp_mem_set_pair_second(m, list_last, new_list_last);
            lsp_mem_dec_ref(m, new_list_last);
        }

        list_last = new_list_last;
    }

    for (uint8_t i = 0; status == LSP_SUCCESS && lsp_functions[i].name; ++i) {
        lsp_addr_t symbol;
        status =
            lsp_mem_create_symbol_from_char(m, lsp_functions[i].name, &symbol);
        if (status != LSP_SUCCESS)
            break;

        lsp_addr_t value;
        status = lsp_mem_create_builtin_function(m, i, &value);
        if (status != LSP_SUCCESS) {
            lsp_mem_dec_ref(m, symbol);
            break;
        }

        lsp_addr_t entry;
        status = lsp_mem_create_pair(m, symbol, value, &entry);
        lsp_mem_dec_ref(m, symbol);
        lsp_mem_dec_ref(m, value);
        if (status != LSP_SUCCESS)
            break;

        lsp_addr_t new_list_last;
        status = lsp_mem_create_pair(m, entry, m->nil, &new_list_last);
        lsp_mem_dec_ref(m, entry);
        if (status != LSP_SUCCESS)
            break;

        if (list == m->nil) {
            list = new_list_last;

        } else {
            lsp_mem_set_pair_second(m, list_last, new_list_last);
            lsp_mem_dec_ref(m, new_list_last);
        }

        list_last = new_list_last;
    }

    if (status == LSP_SUCCESS)
        status = lsp_mem_create_pair(m, list, m->nil, ctx);

    lsp_mem_dec_ref(m, list);
    return status;
}


lsp_status_t lsp_ctx_copy(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t *result) {
    lsp_addr_t list = lsp_mem_get_pair_first(m, ctx);
    return lsp_mem_create_pair(m, list, m->nil, result);
}


lsp_status_t lsp_ctx_add(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t symbol,
                         lsp_addr_t value) {
    lsp_status_t status;

    if (contains_symbol(m, ctx, symbol)) {
        status = remove_symbol(m, ctx, symbol);
        if (status != LSP_SUCCESS)
            return status;
    }

    lsp_addr_t list = lsp_mem_get_pair_first(m, ctx);

    lsp_addr_t entry;
    status = lsp_mem_create_pair(m, symbol, value, &entry);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_mem_create_pair(m, entry, list, &list);
    lsp_mem_dec_ref(m, entry);
    if (status != LSP_SUCCESS)
        return status;

    lsp_mem_set_pair_first(m, ctx, list);
    lsp_mem_dec_ref(m, list);
    return LSP_SUCCESS;
}


lsp_status_t lsp_ctx_set(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t symbol,
                         lsp_addr_t value) {
    lsp_addr_t list = lsp_mem_get_pair_first(m, ctx);

    while (list != m->nil) {
        lsp_addr_t entry = lsp_mem_get_pair_first(m, list);
        lsp_addr_t entry_symbol = lsp_mem_get_pair_first(m, entry);

        if (lsp_mem_eq(m, symbol, entry_symbol)) {
            lsp_mem_set_pair_second(m, entry, value);
            return LSP_SUCCESS;
        }

        list = lsp_mem_get_pair_second(m, list);
    }

    return LSP_ERR_CTX;
}


lsp_status_t lsp_ctx_get(lsp_mem_t *m, lsp_addr_t ctx, lsp_addr_t symbol,
                         lsp_addr_t *value) {
    lsp_addr_t list = lsp_mem_get_pair_first(m, ctx);

    while (list != m->nil) {
        lsp_addr_t entry = lsp_mem_get_pair_first(m, list);
        lsp_addr_t entry_symbol = lsp_mem_get_pair_first(m, entry);

        if (lsp_mem_eq(m, symbol, entry_symbol)) {
            *value = lsp_mem_get_pair_second(m, entry);
            return lsp_mem_inc_ref(m, *value);
        }

        list = lsp_mem_get_pair_second(m, list);
    }

    return LSP_ERR_CTX;
}
