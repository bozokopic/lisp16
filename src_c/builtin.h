#ifndef LISP16_BUILTIN_H
#define LISP16_BUILTIN_H

#include "env.h"


typedef lsp_status_t (*lsp_builtin_cb_t)(lsp_env_t *e, lsp_addr_t ctx,
                                         lsp_addr_t args);

typedef struct {
    char *name;
    lsp_builtin_cb_t cb;
} lsp_builtin_entry_t;


lsp_status_t lsp_builtin_get_args_1(lsp_mem_t *m, lsp_addr_t args,
                                    lsp_addr_t *arg1);
lsp_status_t lsp_builtin_get_args_2(lsp_mem_t *m, lsp_addr_t args,
                                    lsp_addr_t *arg1, lsp_addr_t *arg2);
lsp_status_t lsp_builtin_get_args_3(lsp_mem_t *m, lsp_addr_t args,
                                    lsp_addr_t *arg1, lsp_addr_t *arg2,
                                    lsp_addr_t *arg3);

#endif
