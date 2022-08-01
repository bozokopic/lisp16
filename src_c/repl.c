#include "repl.h"
#include "ctx.h"
#include "write.h"
#include "read.h"
#include "eval.h"


static void log_status(lsp_out_stream_t *s, lsp_status_t status) {
    if (status == LSP_SUCCESS)
        return;

    lsp_out_stream_write_str(s, "error: ");

    if (status == LSP_ERR_MEM) {
        lsp_out_stream_write_str(s, "no memory");

    } else if (status == LSP_ERR_CTX) {
        lsp_out_stream_write_str(s, "can't resolve symbol");

    } else if (status == LSP_ERR_READ) {
        lsp_out_stream_write_str(s, "reader error");

    } else if (status == LSP_ERR_WRITE) {
        lsp_out_stream_write_str(s, "writer error");

    } else if (status == LSP_ERR_EVAL) {
        lsp_out_stream_write_str(s, "evaluation error");

    } else if (status == LSP_ERR_APPLY) {
        lsp_out_stream_write_str(s, "application error");

    } else if (status == LSP_ERR_ARG_COUNT) {
        lsp_out_stream_write_str(s, "invalid argument count");

    } else if (status == LSP_ERR_ARG_TYPE) {
        lsp_out_stream_write_str(s, "invalid argument type");

    } else if (status == LSP_ERR_ARG_VALUE) {
        lsp_out_stream_write_str(s, "invalid argument value");

    } else if (status >= LSP_ERR_USER) {
        lsp_out_stream_write_str(s, "user error ");
        lsp_out_stream_write_int(s, status - LSP_ERR_USER);

    } else {
        lsp_out_stream_write_str(s, "other error");
    }

    lsp_out_stream_write(s, '\n');
}


static lsp_status_t skip_line(lsp_in_stream_t *s) {
    lsp_uint8_t c;
    lsp_status_t status;

    do {
        status = lsp_in_stream_read(s, &c);
    } while (status == LSP_SUCCESS && c != '\n');

    return status;
}


lsp_status_t lsp_repl(lsp_env_t *e, lsp_addr_t ctx) {
    while (true) {
        lsp_addr_t value;
        lsp_status_t status = lsp_read(e->m, e->in, &value);
        if (status == LSP_EOF)
            return status;
        if (status != LSP_SUCCESS) {
            log_status(e->out, status);

            status = skip_line(e->in);
            if (status != LSP_SUCCESS)
                return status;

            continue;
        }

        lsp_addr_t result;
        status = lsp_env_resolve(e, ctx, value, &result);
        lsp_mem_dec_ref(e->m, value);
        if (status == LSP_EOF)
            return status;
        if (status != LSP_SUCCESS) {
            log_status(e->out, status);
            continue;
        }

        if (result == e->m->nil)
            continue;

        status = lsp_write(e->m, e->out, result);
        lsp_mem_dec_ref(e->m, result);
        if (status == LSP_EOF)
            return status;
        if (status != LSP_SUCCESS) {
            log_status(e->out, status);
            continue;
        }
        lsp_out_stream_write(e->out, '\n');
    }
}
