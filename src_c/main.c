#include "ctx.h"
#include "repl.h"

#if LSP_ARCH == LSP_ARCH_POSIX
#include "arch/posix.h"
#elif LSP_ARCH == LSP_ARCH_AVR8
#include "arch/avr8.h"
#elif LSP_ARCH == LSP_ARCH_STM32
#include "arch/stm32.h"
#endif


int main() {
    lsp_mem_t *m = NULL;
    lsp_in_stream_t *in = NULL;
    lsp_out_stream_t *out = NULL;
    lsp_status_t status = LSP_ERR;

    LSP_ARCH_INIT();

    m = LSP_ARCH_CREATE_MEM();
    if (!m)
        goto cleanup;

    in = LSP_ARCH_CREATE_IN_STREAM();
    if (!in)
        goto cleanup;

    out = LSP_ARCH_CREATE_OUT_STREAM();
    if (!out)
        goto cleanup;

    lsp_env_t e;
    lsp_env_init(&e, m, in, out);

    lsp_addr_t ctx;
    status = lsp_ctx_create(m, &ctx);
    if (status != LSP_SUCCESS)
        goto cleanup;

    status = lsp_repl(&e, ctx);
    lsp_mem_dec_ref(m, ctx);

cleanup:
    if (out)
        LSP_ARCH_FREE_OUT_STREAM(out);

    if (in)
        LSP_ARCH_FREE_IN_STREAM(in);

    if (m)
        LSP_ARCH_FREE_MEM(m);

    return ((status == LSP_EOF) ? 0 : 1);
}
