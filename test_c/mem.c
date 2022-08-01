#include "acutest.h"
#include "../src_c/mem.h"

#define MEM_SIZE 32


lsp_int8_t data[sizeof(lsp_mem_t) + MEM_SIZE * sizeof(lsp_cell_t)];


void test_mem_gc() {
    lsp_mem_t *m = (void *)data;
    lsp_mem_init(m, MEM_SIZE);

    for (lsp_int32_t i = 0; i < 10000; ++i) {
        lsp_addr_t addr;
        TEST_ASSERT(lsp_mem_create_number(m, i, &addr) == LSP_SUCCESS);
        lsp_mem_dec_ref(m, addr);
    }
}


void test_mem_no_gc() {
    lsp_int32_t i;
    lsp_mem_t *m = (void *)data;
    lsp_mem_init(m, MEM_SIZE);

    for (i = 0; i < 10000; ++i) {
        lsp_addr_t addr;
        if (lsp_mem_create_number(m, i, &addr) != LSP_SUCCESS)
            break;
    }

    TEST_ASSERT(i > 1 && i < MEM_SIZE);
}


TEST_LIST = {
    {"mem_gc", test_mem_gc}, {"mem_no_gc", test_mem_no_gc}, {NULL, NULL}};
