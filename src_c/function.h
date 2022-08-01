#ifndef LISP16_FUNCTION_H
#define LISP16_FUNCTION_H

#include "builtin.h"


extern lsp_builtin_entry_t lsp_functions[];

lsp_status_t lsp_function_eval(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_apply(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_error(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_cons(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_set_car(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args);
lsp_status_t lsp_function_set_cdr(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args);
lsp_status_t lsp_function_is_number(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args);
lsp_status_t lsp_function_is_pair(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args);
lsp_status_t lsp_function_is_string(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args);
lsp_status_t lsp_function_is_symbol(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args);
lsp_status_t lsp_function_is_function(lsp_env_t *e, lsp_addr_t ctx,
                                      lsp_addr_t args);
lsp_status_t lsp_function_is_syntax(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args);
lsp_status_t lsp_function_eq(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_equal(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_gt(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_lt(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_plus(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_minus(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_multiply(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_divide(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_read(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_read_u8(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args);
lsp_status_t lsp_function_peek_u8(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args);
lsp_status_t lsp_function_write(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);
lsp_status_t lsp_function_write_u8(lsp_env_t *e, lsp_addr_t ctx,
                                   lsp_addr_t args);
lsp_status_t lsp_function_make_string(lsp_env_t *e, lsp_addr_t ctx,
                                      lsp_addr_t args);
lsp_status_t lsp_function_string_length(lsp_env_t *e, lsp_addr_t ctx,
                                        lsp_addr_t args);
lsp_status_t lsp_function_string_ref(lsp_env_t *e, lsp_addr_t ctx,
                                     lsp_addr_t args);
lsp_status_t lsp_function_string_set(lsp_env_t *e, lsp_addr_t ctx,
                                     lsp_addr_t args);

#endif
