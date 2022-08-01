#ifndef LISP16_MEM_H
#define LISP16_MEM_H

#include "cell.h"
#include "status.h"


typedef struct {
    lsp_addr_t nil;
    lsp_addr_t zero;
    lsp_addr_t one;
    lsp_addr_t quote;
    lsp_addr_t quasiquote;
    lsp_addr_t unquote;
    lsp_addr_t unquote_splicing;

    // internal
    lsp_uint16_t size;
    lsp_addr_t last_addr;
    lsp_addr_t root;
    lsp_cell_t cells[];
} lsp_mem_t;


lsp_status_t lsp_mem_init(lsp_mem_t *m, lsp_uint16_t size);
lsp_status_t lsp_mem_inc_ref(lsp_mem_t *m, lsp_addr_t addr);
void lsp_mem_dec_ref(lsp_mem_t *m, lsp_addr_t addr);

lsp_status_t lsp_mem_create_number(lsp_mem_t *m, lsp_int32_t value,
                                   lsp_addr_t *addr);
lsp_status_t lsp_mem_create_pair(lsp_mem_t *m, lsp_addr_t first,
                                 lsp_addr_t second, lsp_addr_t *addr);
lsp_status_t lsp_mem_create_string(lsp_mem_t *m, lsp_uint16_t data_len,
                                   lsp_addr_t *addr);
lsp_status_t lsp_mem_create_symbol_from_string(lsp_mem_t *m, lsp_addr_t str,
                                               lsp_addr_t *addr);
lsp_status_t lsp_mem_create_symbol_from_char(lsp_mem_t *m, char *name,
                                             lsp_addr_t *addr);
lsp_status_t lsp_mem_create_builtin_function(lsp_mem_t *m, lsp_uint16_t index,
                                             lsp_addr_t *addr);
lsp_status_t lsp_mem_create_builtin_syntax(lsp_mem_t *m, lsp_uint16_t index,
                                           lsp_addr_t *addr);
lsp_status_t lsp_mem_create_function(lsp_mem_t *m, lsp_addr_t parent_ctx,
                                     lsp_addr_t args, lsp_addr_t body,
                                     lsp_addr_t *addr);
lsp_status_t lsp_mem_create_syntax(lsp_mem_t *m, lsp_addr_t parent_ctx,
                                   lsp_addr_t args, lsp_addr_t body,
                                   lsp_addr_t *addr);

lsp_bool_t lsp_mem_eq(lsp_mem_t *m, lsp_addr_t a1, lsp_addr_t a2);
lsp_bool_t lsp_mem_equal(lsp_mem_t *m, lsp_addr_t a1, lsp_addr_t a2);


static inline lsp_bool_t lsp_mem_is_number(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_number(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_pair(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_pair(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_string(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_string(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_symbol(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_symbol(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_builtin_function(lsp_mem_t *m,
                                                     lsp_addr_t addr) {
    return lsp_cell_is_builtin_function(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_builtin_syntax(lsp_mem_t *m,
                                                   lsp_addr_t addr) {
    return lsp_cell_is_builtin_syntax(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_function(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_function(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_syntax(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_syntax(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_string_or_symbol(lsp_mem_t *m,
                                                     lsp_addr_t addr) {
    return lsp_cell_is_string_or_symbol(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_builtin(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_is_builtin(m->cells + addr);
}

static inline lsp_bool_t lsp_mem_is_function_or_syntax(lsp_mem_t *m,
                                                       lsp_addr_t addr) {
    return lsp_cell_is_function_or_syntax(m->cells + addr);
}


static inline lsp_int32_t lsp_mem_get_number(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_get_number(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_pair_first(lsp_mem_t *m, lsp_addr_t addr) {
    return lsp_cell_get_pair_first(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_pair_second(lsp_mem_t *m,
                                                 lsp_addr_t addr) {
    return lsp_cell_get_pair_second(m->cells + addr);
}

static inline lsp_uint16_t lsp_mem_get_string_len(lsp_mem_t *m,
                                                  lsp_addr_t addr) {
    return lsp_cell_get_string_len(m->cells + addr);
}

static inline lsp_uint8_t lsp_mem_get_string_data(lsp_mem_t *m, lsp_addr_t addr,
                                                  lsp_uint16_t i) {
    return lsp_cell_get_string_data(m->cells + addr, i);
}

static inline lsp_uint16_t lsp_mem_get_symbol_len(lsp_mem_t *m,
                                                  lsp_addr_t addr) {
    return lsp_cell_get_symbol_len(m->cells + addr);
}

static inline lsp_uint8_t lsp_mem_get_symbol_name(lsp_mem_t *m, lsp_addr_t addr,
                                                  lsp_uint16_t i) {
    return lsp_cell_get_symbol_name(m->cells + addr, i);
}

static inline lsp_uint16_t lsp_mem_get_builtin_index(lsp_mem_t *m,
                                                     lsp_addr_t addr) {
    return lsp_cell_get_builtin_index(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_function_parent_ctx(lsp_mem_t *m,
                                                         lsp_addr_t addr) {
    return lsp_cell_get_function_parent_ctx(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_function_args(lsp_mem_t *m,
                                                   lsp_addr_t addr) {
    return lsp_cell_get_function_args(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_function_body(lsp_mem_t *m,
                                                   lsp_addr_t addr) {
    return lsp_cell_get_function_body(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_syntax_parent_ctx(lsp_mem_t *m,
                                                       lsp_addr_t addr) {
    return lsp_cell_get_syntax_parent_ctx(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_syntax_args(lsp_mem_t *m,
                                                 lsp_addr_t addr) {
    return lsp_cell_get_syntax_args(m->cells + addr);
}

static inline lsp_addr_t lsp_mem_get_syntax_body(lsp_mem_t *m,
                                                 lsp_addr_t addr) {
    return lsp_cell_get_syntax_body(m->cells + addr);
}


static inline void lsp_mem_set_pair_first(lsp_mem_t *m, lsp_addr_t addr,
                                          lsp_addr_t first) {
    lsp_cell_set_pair(m->cells + addr, first,
                      lsp_cell_get_pair_second(m->cells + addr));
}

static inline void lsp_mem_set_pair_second(lsp_mem_t *m, lsp_addr_t addr,
                                           lsp_addr_t second) {
    lsp_cell_set_pair(m->cells + addr, lsp_cell_get_pair_first(m->cells + addr),
                      second);
}

static inline void lsp_mem_set_string_data(lsp_mem_t *m, lsp_addr_t addr,
                                           lsp_uint16_t i, lsp_uint8_t data_i) {
    lsp_cell_set_string_data(m->cells + addr, i, data_i);
}

#endif
