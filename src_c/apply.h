#ifndef LISP16_APPLY_H
#define LISP16_APPLY_H

#include "env.h"


lsp_status_t lsp_apply(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t callable,
                       lsp_addr_t args);

#endif
