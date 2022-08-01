#ifndef LSP_STATUS_H
#define LSP_STATUS_H

#include "arch.h"

#define LSP_STATUS(x) ((lsp_status_t)x)

#define LSP_SUCCESS LSP_STATUS(0)
#define LSP_EOF LSP_STATUS(-1)
#define LSP_ERR LSP_STATUS(1)
#define LSP_ERR_MEM LSP_STATUS(2)
#define LSP_ERR_CTX LSP_STATUS(3)
#define LSP_ERR_READ LSP_STATUS(4)
#define LSP_ERR_WRITE LSP_STATUS(5)
#define LSP_ERR_EVAL LSP_STATUS(6)
#define LSP_ERR_APPLY LSP_STATUS(7)
#define LSP_ERR_ARG_COUNT LSP_STATUS(8)
#define LSP_ERR_ARG_TYPE LSP_STATUS(9)
#define LSP_ERR_ARG_VALUE LSP_STATUS(10)
#define LSP_ERR_USER LSP_STATUS(0x80)


typedef lsp_int8_t lsp_status_t;

#endif
