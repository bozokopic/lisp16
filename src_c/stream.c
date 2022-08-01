#include "stream.h"


static lsp_int16_t str_getchar(lsp_in_stream_t *s) {
    lsp_str_stream_t *ss = (lsp_str_stream_t *)s;

    if (ss->pos >= lsp_mem_get_string_len(ss->m, ss->str))
        return LSP_EOF;

    return lsp_mem_get_string_data(ss->m, ss->str, ss->pos++);
}


void lsp_in_stream_init(lsp_in_stream_t *s, lsp_stream_getchar_t getchar) {
    s->getchar = getchar;
    s->next_available = false;
}


lsp_status_t lsp_in_stream_read(lsp_in_stream_t *s, lsp_uint8_t *v) {
    if (s->next_available) {
        s->next_available = false;
        *v = s->next_value;
        return s->next_status;
    }

    lsp_int16_t c = s->getchar(s);
    *v = c;
    return ((c == LSP_EOF) ? LSP_EOF : LSP_SUCCESS);
}


lsp_status_t lsp_in_stream_peek(lsp_in_stream_t *s, lsp_uint8_t *v) {
    if (s->next_available) {
        *v = s->next_value;
        return s->next_status;
    }

    lsp_int16_t c = s->getchar(s);
    s->next_available = true;
    s->next_value = c;
    s->next_status = ((c == LSP_EOF) ? LSP_EOF : LSP_SUCCESS);

    *v = s->next_value;
    return s->next_status;
}


void lsp_out_stream_init(lsp_out_stream_t *s, lsp_stream_putchar_t putchar) {
    s->putchar = putchar;
}


lsp_status_t lsp_out_stream_write(lsp_out_stream_t *s, lsp_uint8_t v) {
    if (s->putchar(s, v) == LSP_EOF)
        return LSP_EOF;

    return LSP_SUCCESS;
}


lsp_status_t lsp_out_stream_write_str(lsp_out_stream_t *s, char *str) {
    while (*str) {
        lsp_status_t status = lsp_out_stream_write(s, *(str++));
        if (status != LSP_SUCCESS)
            return status;
    }

    return LSP_SUCCESS;
}


lsp_status_t lsp_out_stream_write_int(lsp_out_stream_t *s, lsp_int32_t v) {
    lsp_status_t status;
    if (v < 0) {
        v *= -1;
        status = lsp_out_stream_write(s, '-');
        if (status != LSP_SUCCESS)
            return status;
    }

    lsp_uint8_t size = 0;
    for (lsp_int32_t i = v; i; i /= 10)
        size++;
    if (size < 1)
        size = 1;

    for (lsp_uint8_t i = 0; i < size; ++i) {
        lsp_int32_t temp = v;
        for (lsp_uint8_t j = i; j < size - 1; ++j)
            temp /= 10;

        lsp_uint8_t digit = temp % 10;
        status = lsp_out_stream_write(s, '0' + digit);
        if (status != LSP_SUCCESS)
            return status;
    }

    return LSP_SUCCESS;
}


void lsp_str_stream_init(lsp_str_stream_t *s, lsp_mem_t *m, lsp_addr_t str) {
    lsp_in_stream_init((lsp_in_stream_t *)s, str_getchar);
    s->m = m;
    s->str = str;
    s->pos = 0;
}
