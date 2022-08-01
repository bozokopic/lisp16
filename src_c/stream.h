#ifndef LISP16_STREAM_H
#define LISP16_STREAM_H

#include "mem.h"


typedef struct lsp_in_stream_t lsp_in_stream_t;
typedef struct lsp_out_stream_t lsp_out_stream_t;
typedef lsp_int16_t (*lsp_stream_getchar_t)(lsp_in_stream_t *s);
typedef lsp_int16_t (*lsp_stream_putchar_t)(lsp_out_stream_t *s, lsp_int16_t v);

struct lsp_in_stream_t {
    // internal
    lsp_stream_getchar_t getchar;
    lsp_bool_t next_available;
    lsp_uint8_t next_value;
    lsp_status_t next_status;
};

struct lsp_out_stream_t {
    // internal
    lsp_stream_putchar_t putchar;
};

typedef struct {
    lsp_in_stream_t base;

    // internal
    lsp_mem_t *m;
    lsp_addr_t str;
    lsp_uint16_t pos;
} lsp_str_stream_t;


void lsp_in_stream_init(lsp_in_stream_t *s, lsp_stream_getchar_t getchar);
lsp_status_t lsp_in_stream_read(lsp_in_stream_t *s, lsp_uint8_t *v);
lsp_status_t lsp_in_stream_peek(lsp_in_stream_t *s, lsp_uint8_t *v);

void lsp_out_stream_init(lsp_out_stream_t *s, lsp_stream_putchar_t putchar);
lsp_status_t lsp_out_stream_write(lsp_out_stream_t *s, lsp_uint8_t v);
lsp_status_t lsp_out_stream_write_str(lsp_out_stream_t *s, char *str);
lsp_status_t lsp_out_stream_write_int(lsp_out_stream_t *s, lsp_int32_t v);

void lsp_str_stream_init(lsp_str_stream_t *s, lsp_mem_t *m, lsp_addr_t str);

#endif
