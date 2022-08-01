#include "builtin.h"


lsp_status_t lsp_builtin_get_args_1(lsp_mem_t *m, lsp_addr_t args,
                                    lsp_addr_t *arg1) {
    if (args == m->nil)
        return LSP_ERR_ARG_COUNT;

    *arg1 = lsp_mem_get_pair_first(m, args);

    args = lsp_mem_get_pair_second(m, args);
    if (args != m->nil)
        return LSP_ERR_ARG_COUNT;

    return LSP_SUCCESS;
}


lsp_status_t lsp_builtin_get_args_2(lsp_mem_t *m, lsp_addr_t args,
                                    lsp_addr_t *arg1, lsp_addr_t *arg2) {
    if (args == m->nil)
        return LSP_ERR_ARG_COUNT;

    *arg1 = lsp_mem_get_pair_first(m, args);

    args = lsp_mem_get_pair_second(m, args);
    if (args == m->nil)
        return LSP_ERR_ARG_COUNT;

    *arg2 = lsp_mem_get_pair_first(m, args);

    args = lsp_mem_get_pair_second(m, args);
    if (args != m->nil)
        return LSP_ERR_ARG_COUNT;

    return LSP_SUCCESS;
}


lsp_status_t lsp_builtin_get_args_3(lsp_mem_t *m, lsp_addr_t args,
                                    lsp_addr_t *arg1, lsp_addr_t *arg2,
                                    lsp_addr_t *arg3) {
    if (args == m->nil)
        return LSP_ERR_ARG_COUNT;

    *arg1 = lsp_mem_get_pair_first(m, args);

    args = lsp_mem_get_pair_second(m, args);
    if (args == m->nil)
        return LSP_ERR_ARG_COUNT;

    *arg2 = lsp_mem_get_pair_first(m, args);

    args = lsp_mem_get_pair_second(m, args);
    if (args == m->nil)
        return LSP_ERR_ARG_COUNT;

    *arg3 = lsp_mem_get_pair_first(m, args);

    args = lsp_mem_get_pair_second(m, args);
    if (args != m->nil)
        return LSP_ERR_ARG_COUNT;

    return LSP_SUCCESS;
}
