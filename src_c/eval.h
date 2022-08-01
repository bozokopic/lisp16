#ifndef LISP16_EVAL_H
#define LISP16_EVAL_H

#include "env.h"


lsp_status_t lsp_eval(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t value);

#endif
