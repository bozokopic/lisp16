#ifndef LISP16_CELL_H
#define LISP16_CELL_H

#include "arch.h"


typedef lsp_uint16_t lsp_cell_t;
typedef lsp_uint16_t lsp_addr_t; // 14 least significant bits used


lsp_uint16_t lsp_cell_get_size(lsp_cell_t *c);
lsp_uint16_t lsp_cell_get_number_size(lsp_int32_t value);
lsp_uint16_t lsp_cell_get_string_symbol_size(lsp_uint16_t len);


static inline lsp_bool_t lsp_cell_is_number(lsp_cell_t *c) {
    return (*c & 0x4000) == 0x0000;
}

static inline lsp_bool_t lsp_cell_is_pair(lsp_cell_t *c) {
    return (*c & 0x6000) == 0x4000;
}

static inline lsp_bool_t lsp_cell_is_string(lsp_cell_t *c) {
    return (*c & 0x7800) == 0x6000;
}

static inline lsp_bool_t lsp_cell_is_symbol(lsp_cell_t *c) {
    return (*c & 0x7800) == 0x6800;
}

static inline lsp_bool_t lsp_cell_is_builtin_function(lsp_cell_t *c) {
    return (*c & 0x7c00) == 0x7000;
}

static inline lsp_bool_t lsp_cell_is_builtin_syntax(lsp_cell_t *c) {
    return (*c & 0x7c00) == 0x7400;
}

static inline lsp_bool_t lsp_cell_is_function(lsp_cell_t *c) {
    return (*c & 0x7c00) == 0x7800;
}

static inline lsp_bool_t lsp_cell_is_syntax(lsp_cell_t *c) {
    return (*c & 0x7c00) == 0x7c00;
}

static inline lsp_bool_t lsp_cell_is_string_or_symbol(lsp_cell_t *c) {
    return (*c & 0x7000) == 0x6000;
}

static inline lsp_bool_t lsp_cell_is_builtin(lsp_cell_t *c) {
    return (*c & 0x7800) == 0x7000;
}

static inline lsp_bool_t lsp_cell_is_function_or_syntax(lsp_cell_t *c) {
    return (*c & 0x7800) == 0x7800;
}


static inline void lsp_cell_set_number(lsp_cell_t *c, lsp_int32_t value) {
    lsp_uint8_t size = lsp_cell_get_number_size(value);
    for (lsp_uint8_t i = 0; i < size; ++i) {
        lsp_uint8_t shift = (size - i - 1) * 14;
        c[i] = (value >> shift) & (i ? 0x3fff : 0x1fff);
        if (i != size - 1)
            c[i] |= (i ? 0x4000 : 0x2000);
    }
}

static inline void lsp_cell_set_pair(lsp_cell_t *c, lsp_addr_t first,
                                     lsp_addr_t second) {
    c[0] = 0x4000 | ((first >> 1) & 0x1fff);
    c[1] = ((first & 1) ? 0x4000 : 0) | (second & 0x3fff);
}

static inline void lsp_cell_set_string(lsp_cell_t *c, lsp_uint16_t data_len) {
    lsp_uint16_t size = lsp_cell_get_string_symbol_size(data_len);
    c[0] = 0x6000 | (data_len & 0x07ff);
    for (lsp_uint16_t i = 1; i < size; ++i)
        c[i] = 0;
}

static inline void lsp_cell_set_string_data(lsp_cell_t *c, lsp_uint16_t i,
                                            lsp_uint8_t data_i) {
    lsp_uint32_t bit_count = (lsp_uint32_t)i << 3;
    lsp_uint16_t start_cell = bit_count / 15;
    lsp_uint8_t bit_shift = bit_count % 15;
    lsp_uint16_t mask = 0x7f80 >> bit_shift;
    if (bit_shift < 8) {
        c[1 + start_cell] = (c[1 + start_cell] & ~mask) |
                            ((lsp_uint16_t)data_i << (7 - bit_shift));
    } else {
        c[1 + start_cell] =
            (c[1 + start_cell] & ~mask) | (data_i >> (bit_shift - 7));
        bit_shift = 22 - bit_shift;
        mask = (0xffff << bit_shift) & 0x7fff;
        c[2 + start_cell] = (c[2 + start_cell] & ~mask) |
                            (((lsp_uint16_t)data_i << bit_shift) & mask);
    }
}

static inline void lsp_cell_set_symbol(lsp_cell_t *c, lsp_uint16_t name_len) {
    lsp_uint16_t size = lsp_cell_get_string_symbol_size(name_len);
    c[0] = 0x6800 | (name_len & 0x07ff);
    for (lsp_uint16_t i = 1; i < size; ++i)
        c[i] = 0;
}

static inline void lsp_cell_set_symbol_name(lsp_cell_t *c, lsp_uint16_t i,
                                            lsp_uint8_t name_i) {
    lsp_cell_set_string_data(c, i, name_i);
}

static inline void lsp_cell_set_builtin_function(lsp_cell_t *c,
                                                 lsp_uint16_t index) {
    *c = 0x7000 | (index & 0x03ff);
}

static inline void lsp_cell_set_builtin_syntax(lsp_cell_t *c,
                                               lsp_uint16_t index) {
    *c = 0x7400 | (index & 0x03ff);
}

static inline void lsp_cell_set_function(lsp_cell_t *c, lsp_addr_t parent_ctx,
                                         lsp_addr_t args, lsp_addr_t body) {
    c[0] = 0x7800;
    c[1] = parent_ctx & 0x3fff;
    c[2] = args & 0x3fff;
    c[3] = body & 0x3fff;
}

static inline void lsp_cell_set_syntax(lsp_cell_t *c, lsp_addr_t parent_ctx,
                                       lsp_addr_t args, lsp_addr_t body) {
    c[0] = 0x7c00;
    c[1] = parent_ctx & 0x3fff;
    c[2] = args & 0x3fff;
    c[3] = body & 0x3fff;
}


static inline lsp_int32_t lsp_cell_get_number(lsp_cell_t *c) {
    lsp_int32_t v = ((c[0] & 0x1000) ? -1 : 0);
    v = (v << 12) | (c[0] & 0x0fff);
    if (!(c[0] & 0x2000))
        return v;
    for (lsp_uint8_t i = 1; 1; ++i) {
        v = (v << 14) | (c[1] & 0x3fff);
        if (!(c[i] & 0x4000))
            return v;
    }
}

static inline lsp_addr_t lsp_cell_get_pair_first(lsp_cell_t *c) {
    return ((c[0] & 0x1fff) << 1) + ((c[1] & 0x4000) ? 1 : 0);
}

static inline lsp_addr_t lsp_cell_get_pair_second(lsp_cell_t *c) {
    return c[1] & 0x3fff;
}

static inline lsp_uint16_t lsp_cell_get_string_len(lsp_cell_t *c) {
    return *c & 0x07ff;
}

static inline lsp_uint8_t lsp_cell_get_string_data(lsp_cell_t *c,
                                                   lsp_uint16_t i) {
    lsp_uint32_t bit_count = (lsp_uint32_t)i << 3;
    lsp_uint16_t start_cell = bit_count / 15;
    lsp_uint8_t start_bit = 14 - (bit_count % 15);
    if (start_bit >= 7)
        return (c[1 + start_cell] >> (start_bit - 7)) & 0xff;
    return ((c[1 + start_cell] << (7 - start_bit)) |
            ((c[2 + start_cell] & 0x7fff) >> (8 + start_bit))) &
           0xff;
}

static inline lsp_uint16_t lsp_cell_get_symbol_len(lsp_cell_t *c) {
    return lsp_cell_get_string_len(c);
}

static inline lsp_uint8_t lsp_cell_get_symbol_name(lsp_cell_t *c,
                                                   lsp_uint16_t i) {
    return lsp_cell_get_string_data(c, i);
}

static inline lsp_uint16_t lsp_cell_get_builtin_index(lsp_cell_t *c) {
    return *c & 0x03ff;
}

static inline lsp_addr_t lsp_cell_get_function_parent_ctx(lsp_cell_t *c) {
    return c[1] & 0x3fff;
}

static inline lsp_addr_t lsp_cell_get_function_args(lsp_cell_t *c) {
    return c[2] & 0x3fff;
}

static inline lsp_addr_t lsp_cell_get_function_body(lsp_cell_t *c) {
    return c[3] & 0x3fff;
}

static inline lsp_addr_t lsp_cell_get_syntax_parent_ctx(lsp_cell_t *c) {
    return lsp_cell_get_function_parent_ctx(c);
}

static inline lsp_addr_t lsp_cell_get_syntax_args(lsp_cell_t *c) {
    return lsp_cell_get_function_args(c);
}

static inline lsp_addr_t lsp_cell_get_syntax_body(lsp_cell_t *c) {
    return lsp_cell_get_function_body(c);
}

#endif
