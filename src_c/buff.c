#include "buff.h"


static lsp_status_t update_str(lsp_buff_t *b) {
    lsp_uint16_t value_len =
        ((b->value == b->m->nil) ? 0 : lsp_mem_get_string_len(b->m, b->value));

    lsp_addr_t value;
    lsp_status_t status =
        lsp_mem_create_string(b->m, value_len + b->buff_len, &value);
    if (status != LSP_SUCCESS)
        return status;

    for (lsp_uint16_t i = 0; i < value_len; ++i)
        lsp_mem_set_string_data(b->m, value, i,
                                lsp_mem_get_string_data(b->m, b->value, i));

    for (lsp_uint16_t i = 0; i < b->buff_len; ++i)
        lsp_mem_set_string_data(b->m, value, i + value_len, b->buff[i]);

    lsp_mem_dec_ref(b->m, b->value);
    b->value = value;
    b->buff_len = 0;
    return LSP_SUCCESS;
}


void lsp_buff_init(lsp_buff_t *b, lsp_mem_t *m) {
    b->m = m;
    b->value = m->nil;
    b->buff_len = 0;
}


lsp_status_t lsp_buff_push(lsp_buff_t *b, lsp_uint8_t c) {
    if (b->buff_len + 1 >= LSP_BUFF_SIZE) {
        lsp_status_t status = update_str(b);
        if (status != LSP_SUCCESS)
            return status;
    }

    b->buff[b->buff_len++] = c;
    return LSP_SUCCESS;
}


lsp_status_t lsp_buff_pop(lsp_buff_t *b, lsp_addr_t *value) {
    lsp_status_t status = update_str(b);
    if (status != LSP_SUCCESS)
        return status;

    *value = b->value;
    b->value = b->m->nil;
    return LSP_SUCCESS;
}


void lsp_buff_clear(lsp_buff_t *b) {
    lsp_mem_dec_ref(b->m, b->value);
    b->value = b->m->nil;
}
