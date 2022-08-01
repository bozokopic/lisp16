#include "cell.h"


lsp_uint16_t lsp_cell_get_size(lsp_cell_t *c) {
    if (lsp_cell_is_number(c)) {
        if (!(c[0] & 0x2000))
            return 1;

        for (lsp_uint8_t i = 1; true; ++i) {
            if (!(c[i] & 0x4000))
                return i + 1;
        }

    } else if (lsp_cell_is_pair(c)) {
        return 2;

    } else if (lsp_cell_is_string_or_symbol(c)) {
        return lsp_cell_get_string_symbol_size(*c & 0x07ff);

    } else if (lsp_cell_is_builtin(c)) {
        return 1;

    } else if (lsp_cell_is_function_or_syntax(c)) {
        return 4;
    }

    return 0;
}


lsp_uint16_t lsp_cell_get_number_size(lsp_int32_t value) {
    lsp_bool_t msb = ((value & 0x1000) ? true : false);
    value >>= 13;
    if (value == 0 || value == -1)
        return 1 + ((msb && !value) ? 1 : 0);

    for (lsp_uint8_t i = 0; 1; ++i) {
        msb = ((value & 0x4000) ? 1 : 0);
        value >>= 15;
        if (value == 0 || value == -1)
            return i + 2 + ((msb && !value) ? 1 : 0);
    }

    return 0;
}


lsp_uint16_t lsp_cell_get_string_symbol_size(lsp_uint16_t len) {
    return (((lsp_uint32_t)len << 3) / 15) + ((len % 15) ? 1 : 0) + 1;
}
