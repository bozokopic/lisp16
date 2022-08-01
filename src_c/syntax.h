#ifndef LISP16_SYNTAX_H
#define LISP16_SYNTAX_H

#include "builtin.h"


extern lsp_builtin_entry_t lsp_syntaxes[];

lsp_status_t lsp_syntax_lambda(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_syntax_syntax(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_syntax_define(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_syntax_set(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_syntax_begin(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_syntax_quote(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_syntax_if(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);

#endif
