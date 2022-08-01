#include "read.h"
#include "buff.h"


static inline lsp_bool_t is_ws(lsp_uint8_t v) {
    return (v == ' ') || (v == '\n') || (v == '\r') || (v == '\t');
}


static inline lsp_bool_t is_comment_start(lsp_uint8_t v) { return v == ';'; }


static inline lsp_bool_t is_comment_stop(lsp_uint8_t v) { return v == '\n'; }


static inline lsp_bool_t is_digit(lsp_uint8_t v) {
    return (v >= '0') && (v <= '9');
}


static inline lsp_bool_t is_list_start(lsp_uint8_t v) {
    return (v == '(') || (v == '[') || (v == '{');
}


static inline lsp_bool_t is_list_stop(lsp_uint8_t v) {
    return (v == ')') || (v == ']') || (v == '}');
}


static inline lsp_bool_t is_str_start_stop(lsp_uint8_t v) { return v == '"'; }


static inline lsp_bool_t is_quote(lsp_uint8_t v) { return v == '\''; }


static inline lsp_bool_t is_quasiquote(lsp_uint8_t v) { return v == '`'; }


static inline lsp_bool_t is_unquote(lsp_uint8_t v) { return v == ','; }


static lsp_status_t skip_ws(lsp_in_stream_t *s) {
    while (true) {
        lsp_uint8_t v;
        lsp_status_t status = lsp_in_stream_peek(s, &v);
        if (status != LSP_SUCCESS)
            return status;

        if (is_comment_start(v)) {
            while (!is_comment_stop(v)) {
                status = lsp_in_stream_read(s, &v);
                if (status != LSP_SUCCESS)
                    return status;
            }

            continue;
        }

        if (!is_ws(v))
            return LSP_SUCCESS;

        lsp_in_stream_read(s, &v);
    }
}


static lsp_status_t read_number(lsp_mem_t *m, lsp_in_stream_t *s,
                                lsp_addr_t *addr) {
    lsp_int32_t v = 0;

    while (true) {
        lsp_uint8_t c;
        lsp_status_t status = lsp_in_stream_peek(s, &c);
        if (status != LSP_SUCCESS)
            return status;

        if (is_ws(c) || is_list_start(c) || is_list_stop(c))
            break;

        if (!is_digit(c))
            return LSP_ERR_READ;

        status = lsp_in_stream_read(s, &c);
        if (status != LSP_SUCCESS)
            return status;

        v = (v * 10) + (c - '0');
    }

    if (v == 0) {
        *addr = m->zero;
        return LSP_SUCCESS;
    }

    if (v == 1) {
        *addr = m->one;
        return LSP_SUCCESS;
    }

    return lsp_mem_create_number(m, v, addr);
}


static lsp_status_t read_list(lsp_mem_t *m, lsp_in_stream_t *s,
                              lsp_addr_t *addr) {
    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_read(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    lsp_uint8_t list_end;
    if (c == '(') {
        list_end = ')';
    } else if (c == '[') {
        list_end = ']';
    } else if (c == '{') {
        list_end = '}';
    } else {
        return LSP_ERR_READ;
    }

    lsp_bool_t read_rest = false;
    lsp_bool_t read_stop = false;
    lsp_addr_t rest = m->nil;
    lsp_addr_t last = m->nil;
    *addr = m->nil;

    while (true) {
        status = skip_ws(s);
        if (status != LSP_SUCCESS)
            break;

        status = lsp_in_stream_peek(s, &c);
        if (status != LSP_SUCCESS)
            break;

        if (is_list_stop(c)) {
            status = lsp_in_stream_read(s, &c);
            if (status != LSP_SUCCESS)
                break;

            if (c != list_end) {
                status = LSP_ERR_READ;
                break;
            }

            lsp_mem_set_pair_second(m, last, rest);
            lsp_mem_dec_ref(m, rest);
            return LSP_SUCCESS;
        }

        if (read_stop) {
            status = LSP_ERR_READ;
            break;
        }

        lsp_addr_t el;
        status = lsp_read(m, s, &el);
        if (status != LSP_SUCCESS)
            break;

        if (lsp_mem_is_symbol(m, el) && lsp_mem_get_symbol_len(m, el) == 1 &&
            lsp_mem_get_symbol_name(m, el, 0) == '.') {
            lsp_mem_dec_ref(m, el);

            if (read_rest) {
                status = LSP_ERR_READ;
                break;
            }

            read_rest = true;
            continue;
        }

        if (read_rest) {
            rest = el;
            read_stop = true;
            continue;
        }

        lsp_addr_t new_last;
        status = lsp_mem_create_pair(m, el, m->nil, &new_last);
        lsp_mem_dec_ref(m, el);
        if (status != LSP_SUCCESS)
            break;

        lsp_mem_set_pair_second(m, last, new_last);
        last = new_last;

        if (*addr == m->nil) {
            *addr = last;
        } else {
            lsp_mem_dec_ref(m, last);
        }
    }

    lsp_mem_dec_ref(m, *addr);
    lsp_mem_dec_ref(m, rest);
    return status;
}


static lsp_status_t read_string(lsp_mem_t *m, lsp_in_stream_t *s,
                                lsp_addr_t *addr) {
    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_read(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    if (!is_str_start_stop(c))
        return LSP_ERR_READ;

    lsp_buff_t buff;
    lsp_buff_init(&buff, m);

    lsp_bool_t read_escaped = false;

    while (true) {
        status = lsp_in_stream_read(s, &c);
        if (status != LSP_SUCCESS)
            goto cleanup;

        if (read_escaped) {
            if (c == 'n') {
                status = lsp_buff_push(&buff, '\n');
            } else if (c == 'r') {
                status = lsp_buff_push(&buff, '\r');
            } else if (c == 't') {
                status = lsp_buff_push(&buff, '\t');
            } else if (c == '\\') {
                status = lsp_buff_push(&buff, '\\');
            } else if (c == '"') {
                status = lsp_buff_push(&buff, '"');
            } else {
                status = LSP_ERR_READ;
            }

            if (status != LSP_SUCCESS)
                goto cleanup;

            read_escaped = false;
            continue;
        }

        if (c == '\\') {
            read_escaped = true;
            continue;
        }

        if (is_str_start_stop(c))
            break;

        status = lsp_buff_push(&buff, c);
        if (status != LSP_SUCCESS)
            goto cleanup;
    }

    status = lsp_buff_pop(&buff, addr);

cleanup:
    lsp_buff_clear(&buff);
    return status;
}


static lsp_status_t read_quote(lsp_mem_t *m, lsp_in_stream_t *s,
                               lsp_addr_t *addr) {
    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_read(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    if (!is_quote(c))
        return LSP_ERR_READ;

    lsp_addr_t value;
    status = lsp_read(m, s, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t list;
    status = lsp_mem_create_pair(m, value, m->nil, &list);
    lsp_mem_dec_ref(m, value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_mem_create_pair(m, m->quote, list, addr);
    lsp_mem_dec_ref(m, list);
    return status;
}


static lsp_status_t read_quasiquote(lsp_mem_t *m, lsp_in_stream_t *s,
                                    lsp_addr_t *addr) {
    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_read(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    if (!is_quasiquote(c))
        return LSP_ERR_READ;

    lsp_addr_t value;
    status = lsp_read(m, s, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t list;
    status = lsp_mem_create_pair(m, value, m->nil, &list);
    lsp_mem_dec_ref(m, value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_mem_create_pair(m, m->quasiquote, list, addr);
    lsp_mem_dec_ref(m, list);
    return status;
}


static lsp_status_t read_unquote(lsp_mem_t *m, lsp_in_stream_t *s,
                                 lsp_addr_t *addr) {
    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_read(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    if (!is_unquote(c))
        return LSP_ERR_READ;

    status = lsp_in_stream_peek(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_splicing = (c == '@');
    if (is_splicing) {
        status = lsp_in_stream_read(s, &c);
        if (status != LSP_SUCCESS)
            return status;
    }

    lsp_addr_t value;
    status = lsp_read(m, s, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t list;
    status = lsp_mem_create_pair(m, value, m->nil, &list);
    lsp_mem_dec_ref(m, value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_mem_create_pair(
        m, (is_splicing ? m->unquote_splicing : m->unquote), list, addr);
    lsp_mem_dec_ref(m, list);
    return status;
}


static lsp_status_t read_symbol(lsp_mem_t *m, lsp_in_stream_t *s,
                                lsp_addr_t *addr) {
    lsp_status_t status;

    lsp_buff_t buff;
    lsp_buff_init(&buff, m);

    while (true) {
        lsp_uint8_t c;
        status = lsp_in_stream_peek(s, &c);
        if (status != LSP_SUCCESS)
            goto cleanup;

        if (is_ws(c) || is_list_start(c) || is_list_stop(c))
            break;

        status = lsp_in_stream_read(s, &c);
        if (status != LSP_SUCCESS)
            goto cleanup;

        status = lsp_buff_push(&buff, c);
        if (status != LSP_SUCCESS)
            goto cleanup;
    }

    lsp_addr_t str;
    status = lsp_buff_pop(&buff, &str);
    if (status != LSP_SUCCESS)
        goto cleanup;

    status = lsp_mem_create_symbol_from_string(m, str, addr);
    lsp_mem_dec_ref(m, str);

cleanup:
    lsp_buff_clear(&buff);
    return status;
}


lsp_status_t lsp_read(lsp_mem_t *m, lsp_in_stream_t *s, lsp_addr_t *addr) {
    lsp_status_t status = skip_ws(s);
    if (status != LSP_SUCCESS)
        return status;

    lsp_uint8_t c;
    status = lsp_in_stream_peek(s, &c);
    if (status != LSP_SUCCESS)
        return status;

    if (is_list_start(c))
        return read_list(m, s, addr);

    if (is_str_start_stop(c))
        return read_string(m, s, addr);

    if (is_digit(c))
        return read_number(m, s, addr);

    if (is_quote(c))
        return read_quote(m, s, addr);

    if (is_quasiquote(c))
        return read_quasiquote(m, s, addr);

    if (is_unquote(c))
        return read_unquote(m, s, addr);

    return read_symbol(m, s, addr);
}
