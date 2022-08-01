#include "acutest.h"
#include "../src_c/cell.h"


void test_cell_number() {
    lsp_cell_t c[4];

    lsp_cell_set_number(c, 0);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(c[0] == 0x0000);
    TEST_ASSERT(lsp_cell_get_number(c) == 0);

    lsp_cell_set_number(c, 1);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(c[0] == 0x0001);
    TEST_ASSERT(lsp_cell_get_number(c) == 1);

    lsp_cell_set_number(c, 0x0fff);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(c[0] == 0x0fff);
    TEST_ASSERT(lsp_cell_get_number(c) == 0x0fff);

    lsp_cell_set_number(c, 0x1fff);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(c[0] == 0x2000);
    TEST_ASSERT(c[1] == 0x1fff);
    TEST_ASSERT(lsp_cell_get_number(c) == 0x1fff);

    lsp_cell_set_number(c, 0xffff);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(c[0] == 0x2003);
    TEST_ASSERT(c[1] == 0x3fff);
    TEST_ASSERT(lsp_cell_get_number(c) == 0xffff);

    lsp_cell_set_number(c, 0x7fffffff);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 3);
    TEST_ASSERT(c[0] == 0x2007);
    TEST_ASSERT(c[1] == 0x7fff);
    TEST_ASSERT(c[2] == 0x3fff);
    TEST_ASSERT(lsp_cell_get_number(c) == 0x7fffffff);

    lsp_cell_set_number(c, -1);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(c[0] == 0x1fff);
    TEST_ASSERT(lsp_cell_get_number(c) == -1);

    lsp_cell_set_number(c, -0x1000);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(c[0] == 0x1000);
    TEST_ASSERT(lsp_cell_get_number(c) == -0x1000);

    lsp_cell_set_number(c, -0x2fff);
    TEST_ASSERT(lsp_cell_is_number(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(c[0] == 0x3fff);
    TEST_ASSERT(c[1] == 0x1001);
    TEST_ASSERT(lsp_cell_get_number(c) == -0x2fff);

    c[0] = 0x4000;
    TEST_ASSERT(!lsp_cell_is_number(c));
}


void test_cell_pair() {
    lsp_cell_t c[2];

    lsp_cell_set_pair(c, 1, 2);
    TEST_ASSERT(lsp_cell_is_pair(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(lsp_cell_get_pair_first(c) == 1);
    TEST_ASSERT(lsp_cell_get_pair_second(c) == 2);

    lsp_cell_set_pair(c, 0x3fff, 0x0000);
    TEST_ASSERT(lsp_cell_is_pair(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(lsp_cell_get_pair_first(c) == 0x3fff);
    TEST_ASSERT(lsp_cell_get_pair_second(c) == 0x0000);

    lsp_cell_set_pair(c, 0x0000, 0x3fff);
    TEST_ASSERT(lsp_cell_is_pair(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(lsp_cell_get_pair_first(c) == 0x0000);
    TEST_ASSERT(lsp_cell_get_pair_second(c) == 0x3fff);
}


void test_cell_string() {
    lsp_cell_t c[4];

    lsp_cell_set_string(c, 0);
    TEST_ASSERT(lsp_cell_is_string(c));
    TEST_ASSERT(lsp_cell_is_string_or_symbol(c));
    TEST_ASSERT(!lsp_cell_is_symbol(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(lsp_cell_get_string_len(c) == 0);

    lsp_cell_set_string(c, 1);
    TEST_ASSERT(lsp_cell_is_string(c));
    TEST_ASSERT(lsp_cell_is_string_or_symbol(c));
    TEST_ASSERT(!lsp_cell_is_symbol(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(lsp_cell_get_string_len(c) == 1);
    lsp_cell_set_string_data(c, 0, 0xff);
    TEST_ASSERT(c[1] == 0x7f80);
    TEST_ASSERT(lsp_cell_get_string_data(c, 0) == 0xff);

    lsp_cell_set_string(c, 2);
    TEST_ASSERT(lsp_cell_is_string(c));
    TEST_ASSERT(lsp_cell_is_string_or_symbol(c));
    TEST_ASSERT(!lsp_cell_is_symbol(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 3);
    TEST_ASSERT(lsp_cell_get_string_len(c) == 2);
    lsp_cell_set_string_data(c, 0, 0x00);
    lsp_cell_set_string_data(c, 1, 0xff);
    TEST_ASSERT(c[1] == 0x7f);
    TEST_ASSERT(c[2] == 0x4000);
    TEST_ASSERT(lsp_cell_get_string_data(c, 0) == 0x00);
    TEST_ASSERT(lsp_cell_get_string_data(c, 1) == 0xff);
}


void test_cell_symbol() {
    lsp_cell_t c[4];

    lsp_cell_set_symbol(c, 0);
    TEST_ASSERT(lsp_cell_is_symbol(c));
    TEST_ASSERT(lsp_cell_is_string_or_symbol(c));
    TEST_ASSERT(!lsp_cell_is_string(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(lsp_cell_get_symbol_len(c) == 0);

    lsp_cell_set_symbol(c, 1);
    TEST_ASSERT(lsp_cell_is_symbol(c));
    TEST_ASSERT(lsp_cell_is_string_or_symbol(c));
    TEST_ASSERT(!lsp_cell_is_string(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 2);
    TEST_ASSERT(lsp_cell_get_symbol_len(c) == 1);
    lsp_cell_set_symbol_name(c, 0, 0xff);
    TEST_ASSERT(c[1] == 0x7f80);
    TEST_ASSERT(lsp_cell_get_symbol_name(c, 0) == 0xff);

    lsp_cell_set_symbol(c, 2);
    TEST_ASSERT(lsp_cell_is_symbol(c));
    TEST_ASSERT(lsp_cell_is_string_or_symbol(c));
    TEST_ASSERT(!lsp_cell_is_string(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 3);
    TEST_ASSERT(lsp_cell_get_symbol_len(c) == 2);
    lsp_cell_set_symbol_name(c, 0, 0x00);
    lsp_cell_set_symbol_name(c, 1, 0xff);
    TEST_ASSERT(c[1] == 0x7f);
    TEST_ASSERT(c[2] == 0x4000);
    TEST_ASSERT(lsp_cell_get_symbol_name(c, 0) == 0x00);
    TEST_ASSERT(lsp_cell_get_symbol_name(c, 1) == 0xff);
}


void test_cell_builtin_function() {
    lsp_cell_t c[1];

    lsp_cell_set_builtin_function(c, 0);
    TEST_ASSERT(lsp_cell_is_builtin_function(c));
    TEST_ASSERT(lsp_cell_is_builtin(c));
    TEST_ASSERT(!lsp_cell_is_builtin_syntax(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(lsp_cell_get_builtin_index(c) == 0);

    lsp_cell_set_builtin_function(c, 123);
    TEST_ASSERT(lsp_cell_is_builtin_function(c));
    TEST_ASSERT(lsp_cell_is_builtin(c));
    TEST_ASSERT(!lsp_cell_is_builtin_syntax(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(lsp_cell_get_builtin_index(c) == 123);
}


void test_cell_builtin_syntax() {
    lsp_cell_t c[1];

    lsp_cell_set_builtin_syntax(c, 0);
    TEST_ASSERT(lsp_cell_is_builtin_syntax(c));
    TEST_ASSERT(lsp_cell_is_builtin(c));
    TEST_ASSERT(!lsp_cell_is_builtin_function(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(lsp_cell_get_builtin_index(c) == 0);

    lsp_cell_set_builtin_syntax(c, 123);
    TEST_ASSERT(lsp_cell_is_builtin_syntax(c));
    TEST_ASSERT(lsp_cell_is_builtin(c));
    TEST_ASSERT(!lsp_cell_is_builtin_function(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 1);
    TEST_ASSERT(lsp_cell_get_builtin_index(c) == 123);
}


void test_cell_function() {
    lsp_cell_t c[4];

    lsp_cell_set_function(c, 1, 2, 3);
    TEST_ASSERT(lsp_cell_is_function(c));
    TEST_ASSERT(lsp_cell_is_function_or_syntax(c));
    TEST_ASSERT(!lsp_cell_is_syntax(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 4);
    TEST_ASSERT(lsp_cell_get_function_parent_ctx(c) == 1);
    TEST_ASSERT(lsp_cell_get_function_args(c) == 2);
    TEST_ASSERT(lsp_cell_get_function_body(c) == 3);
}


void test_cell_syntax() {
    lsp_cell_t c[4];

    lsp_cell_set_syntax(c, 1, 2, 3);
    TEST_ASSERT(lsp_cell_is_syntax(c));
    TEST_ASSERT(lsp_cell_is_function_or_syntax(c));
    TEST_ASSERT(!lsp_cell_is_function(c));
    TEST_ASSERT(lsp_cell_get_size(c) == 4);
    TEST_ASSERT(lsp_cell_get_syntax_parent_ctx(c) == 1);
    TEST_ASSERT(lsp_cell_get_syntax_args(c) == 2);
    TEST_ASSERT(lsp_cell_get_syntax_body(c) == 3);
}


TEST_LIST = {{"cell_number", test_cell_number},
             {"cell_pair", test_cell_pair},
             {"cell_string", test_cell_string},
             {"cell_symbol", test_cell_symbol},
             {"cell_builtin_function", test_cell_builtin_function},
             {"cell_builtin_syntax", test_cell_builtin_syntax},
             {"cell_function", test_cell_function},
             {"cell_syntax", test_cell_syntax},
             {NULL, NULL}};
