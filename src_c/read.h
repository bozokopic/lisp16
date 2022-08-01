#ifndef LISP16_READ_H
#define LISP16_READ_H

#include "mem.h"
#include "stream.h"


lsp_status_t lsp_read(lsp_mem_t *m, lsp_in_stream_t *s, lsp_addr_t *addr);

#endif
