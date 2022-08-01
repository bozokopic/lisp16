#include "mem.h"


static inline lsp_bool_t get_mark(lsp_cell_t *c) {
    return ((*c & 0x8000) ? true : false);
}


static inline void set_mark(lsp_cell_t *c, lsp_bool_t mark) {
    if (mark) {
        *c |= 0x8000;
    } else {
        *c &= 0x7fff;
    }
}


static void restore(lsp_mem_t *m, lsp_addr_t addr) {
    while (true) {
        lsp_cell_t *c = m->cells + addr;
        if (!get_mark(c))
            break;

        lsp_uint16_t c_size = lsp_cell_get_size(c);
        for (lsp_uint16_t i = 0; i < c_size; ++i)
            set_mark(c + i, false);

        if (lsp_cell_is_pair(c)) {
            restore(m, lsp_cell_get_pair_first(c));
            addr = lsp_cell_get_pair_second(c);

        } else if (lsp_cell_is_function(c)) {
            restore(m, lsp_cell_get_function_parent_ctx(c));
            restore(m, lsp_cell_get_function_args(c));
            addr = lsp_cell_get_function_body(c);

        } else if (lsp_cell_is_syntax(c)) {
            restore(m, lsp_cell_get_syntax_parent_ctx(c));
            restore(m, lsp_cell_get_syntax_args(c));
            addr = lsp_cell_get_syntax_body(c);
        }
    }
}


static void mark_and_restore(lsp_mem_t *m) {
    for (lsp_addr_t addr = 0; addr < m->size; ++addr)
        set_mark(m->cells + addr, true);

    restore(m, m->nil);
    restore(m, m->zero);
    restore(m, m->one);
    restore(m, m->quote);
    restore(m, m->quasiquote);
    restore(m, m->unquote);
    restore(m, m->unquote_splicing);
    restore(m, m->root);
}


static lsp_bool_t is_free_cell(lsp_mem_t *m, lsp_addr_t addr, lsp_uint16_t size,
                               lsp_addr_t *used_addr) {
    for (lsp_addr_t i = addr; i < addr + size; ++i) {
        if (!get_mark(m->cells + i)) {
            *used_addr = i;
            return false;
        }
    }

    return true;
}


static lsp_status_t find_free_cell(lsp_mem_t *m, lsp_uint16_t size,
                                   lsp_addr_t *addr) {
    if (!size)
        return LSP_ERR_MEM;

    for (lsp_addr_t i = m->last_addr; i < m->size - size; ++i) {
        if (is_free_cell(m, i, size, &i)) {
            *addr = i;
            m->last_addr = i;
            return LSP_SUCCESS;
        }
    }

    for (lsp_addr_t i = 0; i < m->last_addr && i < m->size - size; ++i) {
        if (is_free_cell(m, i, size, &i)) {
            *addr = i;
            m->last_addr = i;
            return LSP_SUCCESS;
        }
    }

    return LSP_ERR_MEM;
}


static lsp_status_t find_free_cell_with_gc(lsp_mem_t *m, lsp_uint16_t size,
                                           lsp_addr_t *addr) {
    lsp_status_t status = find_free_cell(m, size, addr);
    if (status == LSP_SUCCESS)
        return LSP_SUCCESS;

    mark_and_restore(m);

    return find_free_cell(m, size, addr);
}


static lsp_status_t alloc_cell(lsp_mem_t *m, lsp_uint16_t size,
                               lsp_addr_t *addr) {
    lsp_addr_t root;
    lsp_status_t status = find_free_cell_with_gc(m, 2, &root);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_pair(m->cells + root, m->nil, m->root);
    m->root = root;

    status = find_free_cell_with_gc(m, size, addr);
    if (status != LSP_SUCCESS) {
        m->root = lsp_cell_get_pair_second(m->cells + root);
        return status;
    }

    lsp_mem_set_pair_first(m, root, *addr);
    return LSP_SUCCESS;
}


static lsp_bool_t is_symbol_from_string(lsp_mem_t *m, lsp_addr_t symbol,
                                        lsp_addr_t str) {
    lsp_uint16_t str_len = lsp_cell_get_string_len(m->cells + str);
    if (lsp_mem_get_symbol_len(m, symbol) != str_len)
        return false;

    for (lsp_uint16_t i = 0; i < str_len; ++i)
        if (lsp_mem_get_symbol_name(m, symbol, i) !=
            lsp_mem_get_string_data(m, str, i))
            return false;

    return true;
}


static lsp_bool_t is_symbol_from_char(lsp_mem_t *m, lsp_addr_t symbol,
                                      char *name, lsp_uint16_t name_len) {
    if (lsp_mem_get_symbol_len(m, symbol) != name_len)
        return false;

    for (lsp_uint16_t i = 0; i < name_len; ++i)
        if (lsp_mem_get_symbol_name(m, symbol, i) != name[i])
            return false;

    return true;
}


static lsp_status_t find_symbol_from_string(lsp_mem_t *m, lsp_addr_t str,
                                            lsp_addr_t *addr) {
    for (lsp_addr_t i = 0; i < m->size; ++i) {
        if (get_mark(m->cells + i))
            continue;

        if (lsp_cell_is_symbol(m->cells + i) &&
            is_symbol_from_string(m, i, str)) {
            *addr = i;
            return LSP_SUCCESS;
        }

        i += lsp_cell_get_size(m->cells + i) - 1;
    }

    return LSP_ERR;
}


static lsp_status_t find_symbol_from_char(lsp_mem_t *m, char *name,
                                          lsp_uint16_t name_len,
                                          lsp_addr_t *addr) {
    for (lsp_addr_t i = 0; i < m->size; ++i) {
        if (get_mark(m->cells + i))
            continue;

        if (lsp_cell_is_symbol(m->cells + i) &&
            is_symbol_from_char(m, i, name, name_len)) {
            *addr = i;
            return LSP_SUCCESS;
        }

        i += lsp_cell_get_size(m->cells + i) - 1;
    }

    return LSP_ERR;
}


lsp_status_t lsp_mem_init(lsp_mem_t *m, lsp_uint16_t size) {
    m->size = size;
    m->last_addr = 0;

    for (lsp_addr_t addr = 0; addr < size; ++addr)
        set_mark(m->cells + addr, true);

    lsp_status_t status = find_free_cell(m, 2, &(m->nil));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_pair(m->cells + m->nil, m->nil, m->nil);

    status = find_free_cell(m, lsp_cell_get_number_size(0), &(m->zero));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_number(m->cells + m->zero, 0);

    status = find_free_cell(m, lsp_cell_get_number_size(1), &(m->one));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_number(m->cells + m->one, 1);

    status = find_free_cell(m, lsp_cell_get_string_symbol_size(5), &(m->quote));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_symbol(m->cells + m->quote, 5);
    for (lsp_uint16_t i = 0; i < 5; ++i)
        lsp_cell_set_symbol_name(m->cells + m->quote, i, ("quote")[i]);

    status = find_free_cell(m, lsp_cell_get_string_symbol_size(10),
                            &(m->quasiquote));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_symbol(m->cells + m->quasiquote, 10);
    for (lsp_uint16_t i = 0; i < 10; ++i)
        lsp_cell_set_symbol_name(m->cells + m->quasiquote, i,
                                 ("quasiquote")[i]);

    status =
        find_free_cell(m, lsp_cell_get_string_symbol_size(7), &(m->unquote));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_symbol(m->cells + m->unquote, 7);
    for (lsp_uint16_t i = 0; i < 7; ++i)
        lsp_cell_set_symbol_name(m->cells + m->unquote, i, ("unquote")[i]);

    status = find_free_cell(m, lsp_cell_get_string_symbol_size(16),
                            &(m->unquote_splicing));
    if (status != LSP_SUCCESS)
        return status;
    lsp_cell_set_symbol(m->cells + m->unquote_splicing, 16);
    for (lsp_uint16_t i = 0; i < 16; ++i)
        lsp_cell_set_symbol_name(m->cells + m->unquote_splicing, i,
                                 ("unquote-splicing")[i]);

    m->root = m->nil;
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_inc_ref(lsp_mem_t *m, lsp_addr_t addr) {
    if (addr == m->nil || addr == m->zero || addr == m->one || addr == m->quote)
        return LSP_SUCCESS;

    lsp_addr_t root;
    lsp_status_t status = find_free_cell_with_gc(m, 2, &root);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_pair(m->cells + root, addr, m->root);
    m->root = root;
    return LSP_SUCCESS;
}


void lsp_mem_dec_ref(lsp_mem_t *m, lsp_addr_t addr) {
    if (addr == m->nil || addr == m->zero || addr == m->one || addr == m->quote)
        return;

    lsp_addr_t curr_addr = m->root;
    lsp_addr_t prev_addr = m->nil;
    while (curr_addr != m->nil) {
        lsp_addr_t first = lsp_cell_get_pair_first(m->cells + curr_addr);
        lsp_addr_t second = lsp_cell_get_pair_second(m->cells + curr_addr);

        if (first == addr) {
            if (prev_addr == m->nil) {
                m->root = second;

            } else {
                lsp_mem_set_pair_second(m, prev_addr, second);
            }

            return;
        }

        prev_addr = curr_addr;
        curr_addr = second;
    }
}


lsp_status_t lsp_mem_create_number(lsp_mem_t *m, lsp_int32_t value,
                                   lsp_addr_t *addr) {
    lsp_uint16_t size = lsp_cell_get_number_size(value);
    lsp_status_t status = alloc_cell(m, size, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_number(m->cells + *addr, value);
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_pair(lsp_mem_t *m, lsp_addr_t first,
                                 lsp_addr_t second, lsp_addr_t *addr) {
    lsp_status_t status = alloc_cell(m, 2, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_pair(m->cells + *addr, first, second);
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_string(lsp_mem_t *m, lsp_uint16_t data_len,
                                   lsp_addr_t *addr) {
    lsp_uint16_t size = lsp_cell_get_string_symbol_size(data_len);
    lsp_status_t status = alloc_cell(m, size, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_string(m->cells + *addr, data_len);
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_symbol_from_string(lsp_mem_t *m, lsp_addr_t str,
                                               lsp_addr_t *addr) {
    if (find_symbol_from_string(m, str, addr) == LSP_SUCCESS)
        return lsp_mem_inc_ref(m, *addr);

    lsp_uint16_t name_len = lsp_mem_get_string_len(m, str);
    lsp_uint16_t size = lsp_cell_get_string_symbol_size(name_len);
    lsp_status_t status = alloc_cell(m, size, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_symbol(m->cells + *addr, name_len);
    for (lsp_uint16_t i = 0; i < name_len; ++i)
        lsp_cell_set_symbol_name(m->cells + *addr, i,
                                 lsp_mem_get_string_data(m, str, i));

    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_symbol_from_char(lsp_mem_t *m, char *name,
                                             lsp_addr_t *addr) {
    lsp_uint16_t name_len = 0;
    while (name[name_len])
        name_len++;

    if (find_symbol_from_char(m, name, name_len, addr) == LSP_SUCCESS)
        return lsp_mem_inc_ref(m, *addr);

    lsp_uint16_t size = lsp_cell_get_string_symbol_size(name_len);
    lsp_status_t status = alloc_cell(m, size, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_symbol(m->cells + *addr, name_len);
    for (lsp_uint16_t i = 0; i < name_len; ++i)
        lsp_cell_set_symbol_name(m->cells + *addr, i, name[i]);

    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_builtin_function(lsp_mem_t *m, lsp_uint16_t index,
                                             lsp_addr_t *addr) {
    lsp_status_t status = alloc_cell(m, 1, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_builtin_function(m->cells + *addr, index);
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_builtin_syntax(lsp_mem_t *m, lsp_uint16_t index,
                                           lsp_addr_t *addr) {
    lsp_status_t status = alloc_cell(m, 1, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_builtin_syntax(m->cells + *addr, index);
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_function(lsp_mem_t *m, lsp_addr_t parent_ctx,
                                     lsp_addr_t args, lsp_addr_t body,
                                     lsp_addr_t *addr) {
    lsp_status_t status = alloc_cell(m, 4, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_function(m->cells + *addr, parent_ctx, args, body);
    return LSP_SUCCESS;
}


lsp_status_t lsp_mem_create_syntax(lsp_mem_t *m, lsp_addr_t parent_ctx,
                                   lsp_addr_t args, lsp_addr_t body,
                                   lsp_addr_t *addr) {
    lsp_status_t status = alloc_cell(m, 4, addr);
    if (status != LSP_SUCCESS)
        return status;

    lsp_cell_set_syntax(m->cells + *addr, parent_ctx, args, body);
    return LSP_SUCCESS;
}


lsp_bool_t lsp_mem_eq(lsp_mem_t *m, lsp_addr_t a1, lsp_addr_t a2) {
    if (a1 == a2)
        return true;

    if (lsp_mem_is_number(m, a1)) {
        if (!lsp_mem_is_number(m, a2))
            return false;

        return lsp_mem_get_number(m, a1) == lsp_mem_get_number(m, a2);
    }

    return false;
}


lsp_bool_t lsp_mem_equal(lsp_mem_t *m, lsp_addr_t a1, lsp_addr_t a2) {
    if (lsp_mem_eq(m, a1, a2))
        return true;

    if (lsp_mem_is_pair(m, a1)) {
        if (!lsp_mem_is_pair(m, a2))
            return false;

        while (a1 != m->nil && a2 != m->nil) {
            if (!lsp_mem_equal(m, lsp_mem_get_pair_first(m, a1),
                               lsp_mem_get_pair_first(m, a2)))
                return false;

            a1 = lsp_mem_get_pair_second(m, a1);
            a2 = lsp_mem_get_pair_second(m, a2);
        }

        return a1 == a2;
    }

    if (lsp_mem_is_string(m, a1)) {
        if (!lsp_mem_is_string(m, a2))
            return false;

        lsp_uint16_t a1_len = lsp_mem_get_string_len(m, a1);
        lsp_uint16_t a2_len = lsp_mem_get_string_len(m, a2);
        if (a1_len != a2_len)
            return false;

        for (lsp_uint16_t i = 0; i < a1_len; ++i) {
            if (lsp_mem_get_string_data(m, a1, i) !=
                lsp_mem_get_string_data(m, a2, i))
                return false;
        }

        return true;
    }

    return false;
}
