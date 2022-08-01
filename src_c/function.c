#include "function.h"
#include "apply.h"
#include "eval.h"
#include "read.h"
#include "write.h"


lsp_builtin_entry_t lsp_functions[] = {
    {"eval", lsp_function_eval},
    {"apply", lsp_function_apply},
    {"error", lsp_function_error},
    {"cons", lsp_function_cons},
    {"set-car!", lsp_function_set_car},
    {"set-cdr!", lsp_function_set_cdr},
    {"number?", lsp_function_is_number},
    {"pair?", lsp_function_is_pair},
    {"string?", lsp_function_is_string},
    {"symbol?", lsp_function_is_symbol},
    {"function?", lsp_function_is_function},
    {"syntax?", lsp_function_is_syntax},
    {"eq?", lsp_function_eq},
    {"equal?", lsp_function_equal},
    {">", lsp_function_gt},
    {"<", lsp_function_lt},
    {"+", lsp_function_plus},
    {"-", lsp_function_minus},
    {"*", lsp_function_multiply},
    {"/", lsp_function_divide},
    {"read", lsp_function_read},
    {"read-u8", lsp_function_read_u8},
    {"peek-u8", lsp_function_peek_u8},
    {"write", lsp_function_write},
    {"write-u8", lsp_function_write_u8},
    {"make-string", lsp_function_make_string},
    {"string-length", lsp_function_string_length},
    {"string-ref", lsp_function_string_ref},
    {"string-set!", lsp_function_string_set},
    {NULL, NULL}};


lsp_status_t lsp_function_eval(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_eval(e, ctx, value);
}


lsp_status_t lsp_function_apply(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t callable;
    lsp_addr_t arguments;
    lsp_status_t status =
        lsp_builtin_get_args_2(e->m, args, &callable, &arguments);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_builtin(e->m, callable) &&
        !lsp_mem_is_function_or_syntax(e->m, callable))
        return LSP_ERR_ARG_TYPE;

    return lsp_apply(e, ctx, callable, arguments);
}


lsp_status_t lsp_function_error(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_number(e->m, value))
        return LSP_ERR_ARG_TYPE;

    lsp_int32_t code = lsp_mem_get_number(e->m, value);
    if (code < 0 || code > 126)
        return LSP_ERR_ARG_VALUE;

    return LSP_ERR_USER + code;
}


lsp_status_t lsp_function_cons(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t first;
    lsp_addr_t second;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &first, &second);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t result;
    status = lsp_mem_create_pair(e->m, first, second, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_set_car(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args) {
    lsp_addr_t pair;
    lsp_addr_t first;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &pair, &first);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_pair(e->m, pair))
        return LSP_ERR_ARG_TYPE;

    if (pair == e->m->nil)
        return LSP_ERR_ARG_VALUE;

    lsp_mem_set_pair_first(e->m, pair, first);
    return lsp_env_set_result_value(e, e->m->nil);
}


lsp_status_t lsp_function_set_cdr(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args) {
    lsp_addr_t pair;
    lsp_addr_t second;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &pair, &second);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_pair(e->m, pair))
        return LSP_ERR_ARG_TYPE;

    if (pair == e->m->nil)
        return LSP_ERR_ARG_VALUE;

    lsp_mem_set_pair_second(e->m, pair, second);
    return lsp_env_set_result_value(e, e->m->nil);
}


lsp_status_t lsp_function_is_number(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_number = lsp_mem_is_number(e->m, value);
    return lsp_env_set_result_value(e, (is_number ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_is_pair(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_pair = lsp_mem_is_pair(e->m, value);
    return lsp_env_set_result_value(e, (is_pair ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_is_string(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_string = lsp_mem_is_string(e->m, value);
    return lsp_env_set_result_value(e, (is_string ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_is_symbol(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_symbol = lsp_mem_is_symbol(e->m, value);
    return lsp_env_set_result_value(e, (is_symbol ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_is_function(lsp_env_t *e, lsp_addr_t ctx,
                                      lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_function = lsp_mem_is_function(e->m, value) ||
                             lsp_mem_is_builtin_function(e->m, value);
    return lsp_env_set_result_value(e, (is_function ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_is_syntax(lsp_env_t *e, lsp_addr_t ctx,
                                    lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_syntax = lsp_mem_is_syntax(e->m, value) ||
                           lsp_mem_is_builtin_syntax(e->m, value);
    return lsp_env_set_result_value(e, (is_syntax ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_eq(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t first;
    lsp_addr_t second;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &first, &second);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_eq = lsp_mem_eq(e->m, first, second);
    return lsp_env_set_result_value(e, (is_eq ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_equal(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t first;
    lsp_addr_t second;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &first, &second);
    if (status != LSP_SUCCESS)
        return status;

    lsp_bool_t is_equal = lsp_mem_equal(e->m, first, second);
    return lsp_env_set_result_value(e, (is_equal ? e->m->one : e->m->zero));
}


lsp_status_t lsp_function_gt(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t last_value = e->m->nil;

    while (args != e->m->nil) {
        lsp_addr_t value = lsp_mem_get_pair_first(e->m, args);
        if (!lsp_mem_is_number(e->m, value))
            return LSP_ERR_ARG_TYPE;

        if (last_value != e->m->nil && lsp_mem_get_number(e->m, last_value) <=
                                           lsp_mem_get_number(e->m, value))
            return lsp_env_set_result_value(e, e->m->zero);

        last_value = value;
        args = lsp_mem_get_pair_second(e->m, args);
    }

    return lsp_env_set_result_value(e, e->m->one);
}


lsp_status_t lsp_function_lt(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t last_value = e->m->nil;

    while (args != e->m->nil) {
        lsp_addr_t value = lsp_mem_get_pair_first(e->m, args);
        if (!lsp_mem_is_number(e->m, value))
            return LSP_ERR_ARG_TYPE;

        if (last_value != e->m->nil && lsp_mem_get_number(e->m, last_value) >=
                                           lsp_mem_get_number(e->m, value))
            return lsp_env_set_result_value(e, e->m->zero);

        last_value = value;
        args = lsp_mem_get_pair_second(e->m, args);
    }

    return lsp_env_set_result_value(e, e->m->one);
}


lsp_status_t lsp_function_plus(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_int32_t value = 0;

    while (args != e->m->nil) {
        lsp_addr_t i = lsp_mem_get_pair_first(e->m, args);
        if (!lsp_mem_is_number(e->m, i))
            return LSP_ERR_ARG_TYPE;

        value += lsp_mem_get_number(e->m, i);
        args = lsp_mem_get_pair_second(e->m, args);
    }

    lsp_addr_t result;
    lsp_status_t status = lsp_mem_create_number(e->m, value, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_minus(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_int32_t value;
    lsp_uint16_t counter = 0;

    while (args != e->m->nil) {
        lsp_addr_t i = lsp_mem_get_pair_first(e->m, args);
        if (!lsp_mem_is_number(e->m, i))
            return LSP_ERR_ARG_TYPE;

        if (++counter > 1) {
            value -= lsp_mem_get_number(e->m, i);
        } else {
            value = lsp_mem_get_number(e->m, i);
        }

        args = lsp_mem_get_pair_second(e->m, args);
    }

    if (!counter)
        return LSP_ERR_ARG_COUNT;

    if (counter < 2)
        value = -value;

    lsp_addr_t result;
    lsp_status_t status = lsp_mem_create_number(e->m, value, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_multiply(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_int32_t value = 1;

    while (args != e->m->nil) {
        lsp_addr_t i = lsp_mem_get_pair_first(e->m, args);
        if (!lsp_mem_is_number(e->m, i))
            return LSP_ERR_ARG_TYPE;

        value *= lsp_mem_get_number(e->m, i);
        args = lsp_mem_get_pair_second(e->m, args);
    }

    lsp_addr_t result;
    lsp_status_t status = lsp_mem_create_number(e->m, value, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_divide(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_int32_t value;
    lsp_uint16_t counter = 0;

    while (args != e->m->nil) {
        lsp_addr_t i = lsp_mem_get_pair_first(e->m, args);
        if (!lsp_mem_is_number(e->m, i))
            return LSP_ERR_ARG_TYPE;

        if (++counter > 1) {
            value /= lsp_mem_get_number(e->m, i);
        } else {
            value = lsp_mem_get_number(e->m, i);
        }

        args = lsp_mem_get_pair_second(e->m, args);
    }

    if (!counter)
        return LSP_ERR_ARG_COUNT;

    if (counter < 2)
        value = 1 / value;

    lsp_addr_t result;
    lsp_status_t status = lsp_mem_create_number(e->m, value, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}



lsp_status_t lsp_function_read(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    if (args != e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_addr_t value;
    lsp_status_t status = lsp_read(e->m, e->in, &value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, value);
    lsp_mem_dec_ref(e->m, value);
    return status;
}


lsp_status_t lsp_function_read_u8(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args) {
    if (args != e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_read(e->in, &c);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t result;
    status = lsp_mem_create_number(e->m, c, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_peek_u8(lsp_env_t *e, lsp_addr_t ctx,
                                  lsp_addr_t args) {
    if (args != e->m->nil)
        return LSP_ERR_ARG_COUNT;

    lsp_uint8_t c;
    lsp_status_t status = lsp_in_stream_peek(e->in, &c);
    if (status != LSP_SUCCESS)
        return status;

    lsp_addr_t result;
    status = lsp_mem_create_number(e->m, c, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_write(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_write(e->m, e->out, value);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_env_set_result_value(e, e->m->nil);
}


lsp_status_t lsp_function_write_u8(lsp_env_t *e, lsp_addr_t ctx,
                                   lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_number(e->m, value))
        return LSP_ERR_ARG_TYPE;

    lsp_uint8_t c = lsp_mem_get_number(e->m, value);
    status = lsp_out_stream_write(e->out, c);
    if (status != LSP_SUCCESS)
        return status;

    return lsp_env_set_result_value(e, e->m->nil);
}


lsp_status_t lsp_function_make_string(lsp_env_t *e, lsp_addr_t ctx,
                                      lsp_addr_t args) {
    lsp_addr_t value;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &value);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_number(e->m, value))
        return LSP_ERR_ARG_TYPE;

    lsp_uint16_t str_len = lsp_mem_get_number(e->m, value);

    lsp_addr_t result;
    status = lsp_mem_create_string(e->m, str_len, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_string_length(lsp_env_t *e, lsp_addr_t ctx,
                                        lsp_addr_t args) {
    lsp_addr_t str;
    lsp_status_t status = lsp_builtin_get_args_1(e->m, args, &str);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_string(e->m, str))
        return LSP_ERR_ARG_TYPE;

    lsp_uint16_t str_len = lsp_mem_get_string_len(e->m, str);

    lsp_addr_t result;
    status = lsp_mem_create_number(e->m, str_len, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_string_ref(lsp_env_t *e, lsp_addr_t ctx,
                                     lsp_addr_t args) {
    lsp_addr_t str;
    lsp_addr_t index;
    lsp_status_t status = lsp_builtin_get_args_2(e->m, args, &str, &index);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_string(e->m, str) || !lsp_mem_is_number(e->m, index))
        return LSP_ERR_ARG_TYPE;

    lsp_uint16_t i = lsp_mem_get_number(e->m, index);
    lsp_uint16_t str_len = lsp_mem_get_string_len(e->m, str);
    if (i >= str_len)
        return LSP_ERR_ARG_VALUE;

    lsp_uint8_t c = lsp_mem_get_string_data(e->m, str, i);

    lsp_addr_t result;
    status = lsp_mem_create_number(e->m, c, &result);
    if (status != LSP_SUCCESS)
        return status;

    status = lsp_env_set_result_value(e, result);
    lsp_mem_dec_ref(e->m, result);
    return status;
}


lsp_status_t lsp_function_string_set(lsp_env_t *e, lsp_addr_t ctx,
                                     lsp_addr_t args) {
    lsp_addr_t str;
    lsp_addr_t index;
    lsp_addr_t value;
    lsp_status_t status =
        lsp_builtin_get_args_3(e->m, args, &str, &index, &value);
    if (status != LSP_SUCCESS)
        return status;

    if (!lsp_mem_is_string(e->m, str) || !lsp_mem_is_number(e->m, index) ||
        !lsp_mem_is_number(e->m, value))
        return LSP_ERR_ARG_TYPE;

    lsp_uint16_t i = lsp_mem_get_number(e->m, index);
    lsp_uint16_t str_len = lsp_mem_get_string_len(e->m, str);
    if (i >= str_len)
        return LSP_ERR_ARG_VALUE;

    lsp_mem_set_string_data(e->m, str, i, lsp_mem_get_number(e->m, value));

    return lsp_env_set_result_value(e, e->m->nil);
}
