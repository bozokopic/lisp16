#include "write.h"
#include "function.h"
#include "syntax.h"


static lsp_status_t write_number(lsp_mem_t *m, lsp_out_stream_t *s,
                                 lsp_addr_t addr) {
    return lsp_out_stream_write_int(s, lsp_mem_get_number(m, addr));
}


static lsp_status_t write_pair(lsp_mem_t *m, lsp_out_stream_t *s,
                               lsp_addr_t addr) {
    lsp_status_t status = lsp_out_stream_write(s, '(');
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t write_space = false;
    while (addr != m->nil) {
        if (write_space) {
            lsp_out_stream_write(s, ' ');
        } else {
            write_space = true;
        }

        lsp_addr_t first = lsp_mem_get_pair_first(m, addr);
        lsp_addr_t second = lsp_mem_get_pair_second(m, addr);

        status = lsp_write(m, s, first);
        if (status != LSP_SUCCESS)
            return status;

        if (!lsp_mem_is_pair(m, second)) {
            status = lsp_out_stream_write_str(s, " . ");
            if (status != LSP_SUCCESS)
                return status;

            status = lsp_write(m, s, second);
            if (status != LSP_SUCCESS)
                return status;

            break;
        }

        addr = second;
    }

    return lsp_out_stream_write(s, ')');
}


static lsp_status_t write_string(lsp_mem_t *m, lsp_out_stream_t *s,
                                 lsp_addr_t addr) {
    lsp_uint16_t len = lsp_mem_get_string_len(m, addr);
    lsp_status_t status = lsp_out_stream_write(s, '"');

    for (lsp_uint16_t i = 0; i < len; ++i) {
        lsp_uint8_t c = lsp_mem_get_string_data(m, addr, i);

        if (c == '"') {
            status = lsp_out_stream_write(s, '\\');
            if (status != LSP_SUCCESS)
                return status;
        }

        status = lsp_out_stream_write(s, c);
        if (status != LSP_SUCCESS)
            return status;
    }

    return lsp_out_stream_write(s, '"');
}


static lsp_status_t write_symbol(lsp_mem_t *m, lsp_out_stream_t *s,
                                 lsp_addr_t addr) {
    lsp_uint16_t len = lsp_mem_get_symbol_len(m, addr);

    for (lsp_uint16_t i = 0; i < len; ++i) {
        lsp_uint8_t c = lsp_mem_get_symbol_name(m, addr, i);
        lsp_status_t status = lsp_out_stream_write(s, c);
        if (status != LSP_SUCCESS)
            return status;
    }

    return LSP_SUCCESS;
}


static lsp_status_t write_builtin_function(lsp_mem_t *m, lsp_out_stream_t *s,
                                           lsp_addr_t addr) {
    lsp_status_t status = lsp_out_stream_write_str(s, "#<builtin-function-");
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_out_stream_write_str(
        s, lsp_functions[lsp_mem_get_builtin_index(m, addr)].name);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_out_stream_write(s, '>');
}


static lsp_status_t write_builtin_syntax(lsp_mem_t *m, lsp_out_stream_t *s,
                                         lsp_addr_t addr) {
    lsp_status_t status = lsp_out_stream_write_str(s, "#<builtin-syntax-");
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_out_stream_write_str(
        s, lsp_syntaxes[lsp_mem_get_builtin_index(m, addr)].name);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_out_stream_write(s, '>');
}


static lsp_status_t write_function(lsp_mem_t *m, lsp_out_stream_t *s,
                                   lsp_addr_t addr) {
    lsp_status_t status = lsp_out_stream_write_str(s, "#<function-");
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_out_stream_write_int(s, addr);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_out_stream_write(s, '>');
}


static lsp_status_t write_syntax(lsp_mem_t *m, lsp_out_stream_t *s,
                                 lsp_addr_t addr) {
    lsp_status_t status = lsp_out_stream_write_str(s, "#<syntax-");
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_out_stream_write_int(s, addr);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_out_stream_write(s, '>');
}


lsp_status_t lsp_write(lsp_mem_t *m, lsp_out_stream_t *s, lsp_addr_t addr) {
    if (lsp_mem_is_number(m, addr))
        return write_number(m, s, addr);

    if (lsp_mem_is_pair(m, addr))
        return write_pair(m, s, addr);

    if (lsp_mem_is_string(m, addr))
        return write_string(m, s, addr);

    if (lsp_mem_is_symbol(m, addr))
        return write_symbol(m, s, addr);

    if (lsp_mem_is_builtin_function(m, addr))
        return write_builtin_function(m, s, addr);

    if (lsp_mem_is_builtin_syntax(m, addr))
        return write_builtin_syntax(m, s, addr);

    if (lsp_mem_is_function(m, addr))
        return write_function(m, s, addr);

    if (lsp_mem_is_syntax(m, addr))
        return write_syntax(m, s, addr);

    return LSP_ERR_WRITE;
}
