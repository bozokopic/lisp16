#include "posix.h"
#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 0x4000


static lsp_int16_t posix_getchar(lsp_in_stream_t *s) {
    int c = getchar();
    if (c == EOF)
        return LSP_EOF;
    return c;
}


static lsp_int16_t posix_putchar(lsp_out_stream_t *s, lsp_int16_t c) {
    return putchar(c);
}


void lsp_arch_posix_init() {}


lsp_mem_t *lsp_arch_posix_create_mem() {
    lsp_mem_t *m = malloc(sizeof(lsp_mem_t) + sizeof(lsp_cell_t) * MEM_SIZE);
    if (lsp_mem_init(m, MEM_SIZE) != LSP_SUCCESS) {
        free(m);
        return NULL;
    }
    return m;
}


void lsp_arch_posix_free_mem(lsp_mem_t *m) { free(m); }


lsp_in_stream_t *lsp_arch_posix_create_in_stream() {
    lsp_in_stream_t *s = malloc(sizeof(lsp_in_stream_t));
    lsp_in_stream_init(s, posix_getchar);
    return s;
}


void lsp_arch_posix_free_in_stream(lsp_in_stream_t *s) { free(s); }


lsp_out_stream_t *lsp_arch_posix_create_out_stream() {
    lsp_out_stream_t *s = malloc(sizeof(lsp_out_stream_t));
    lsp_out_stream_init(s, posix_putchar);
    return s;
}


void lsp_arch_posix_free_out_stream(lsp_out_stream_t *s) { free(s); }
