#ifndef LISP16_WRITE_H
#define LISP16_WRITE_H

#include "mem.h"
#include "stream.h"


lsp_status_t lsp_write(lsp_mem_t *m, lsp_out_stream_t *s, lsp_addr_t addr);

#endif
