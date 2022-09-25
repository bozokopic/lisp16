Search.setIndex({"docnames": ["apply", "arch", "buff", "builtin", "cell", "ctx", "env", "eval", "examples", "extensions", "function", "index", "introduction", "main", "mem", "read", "repl", "status", "stream", "syntax", "write"], "filenames": ["apply.rst", "arch.rst", "buff.rst", "builtin.rst", "cell.rst", "ctx.rst", "env.rst", "eval.rst", "examples.rst", "extensions.rst", "function.rst", "index.rst", "introduction.rst", "main.rst", "mem.rst", "read.rst", "repl.rst", "status.rst", "stream.rst", "syntax.rst", "write.rst"], "titles": ["Function/syntax application", "Architecture abstraction layer", "String buffer", "Builtin", "Data types", "Context", "Environment", "Evaluation", "Examples", "Extensions", "Builtin functions", "lisp16", "Introduction", "Main", "Memory management", "Data reader", "REPL", "Result status codes", "Input/output stream", "Builtin syntaxes", "Data writer"], "terms": {"data": [0, 2, 5, 6, 7, 11, 12, 16, 18], "repres": [0, 1, 3, 4, 6, 7, 10, 12, 14, 15, 16, 17, 18, 19], "togeth": [0, 4, 5, 14, 18], "type": [0, 5, 7, 11, 12, 14, 15, 16, 17, 20], "identif": 0, "contain": [0, 2, 4, 5, 6, 11, 14, 18], "number": [0, 5, 7, 9, 10, 19], "index": [0, 4, 10, 14], "entri": [0, 3, 5, 7, 19], "As": [0, 7, 14], "describ": [0, 1, 3, 7, 17], "previou": [0, 5, 12], "chapter": [0, 1, 3, 7, 12], "each": [0, 1, 3, 4, 5, 7, 12, 14, 17], "pointer": [0, 1, 3, 12, 18], "typedef": [0, 1, 2, 3, 4, 6, 14, 17, 18], "lsp_status_t": [0, 2, 3, 5, 6, 7, 10, 13, 14, 15, 16, 17, 18, 19, 20], "lsp_builtin_cb_t": [0, 3], "lsp_env_t": [0, 3, 6, 7, 10, 13, 16, 19], "e": [0, 1, 3, 6, 7, 10, 13, 16, 19], "lsp_addr_t": [0, 2, 3, 4, 5, 6, 7, 10, 13, 14, 15, 16, 18, 19, 20], "ctx": [0, 3, 6, 7, 10, 13, 16, 19], "arg": [0, 3, 4, 7, 9, 10, 14, 19], "call": [0, 1, 3, 5, 6, 11, 13, 15], "provid": [0, 1, 2, 4, 5, 7, 9, 10, 12, 14, 18, 19, 20], "nativ": 0, "argument": [0, 4, 7, 10, 14, 16, 17, 19], "onli": [0, 4, 5, 12, 14, 15, 16], "differ": [0, 1, 12], "between": [0, 5, 12, 15], "i": [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], "itself": [0, 4, 5, 7, 12, 15, 19], "In": [0, 1, 10, 12, 14, 15, 16, 19], "case": [0, 1, 7, 11, 12, 14, 15, 16], "ar": [0, 1, 2, 3, 4, 7, 8, 9, 11, 14, 15, 17, 19], "previous": [0, 1, 2, 19], "evalu": [0, 5, 6, 9, 10, 11, 16, 17, 19], "thei": [0, 4], "without": [0, 10, 11, 19], "represent": [0, 14, 15, 18, 20], "refer": [0, 5, 6, 14], "parent": [0, 4, 5], "context": [0, 4, 6, 7, 9, 11, 17, 19], "name": [0, 1, 3, 4, 5, 14, 16, 20], "list": [0, 4, 5, 7, 9, 12, 14], "bodi": [0, 4, 9, 14], "dure": [0, 1, 3, 5, 12, 14, 17, 18], "new": [0, 5, 14, 15, 19], "creat": [0, 5, 14, 15], "copi": [0, 5, 11], "associ": [0, 1, 3, 4, 5, 7, 11, 12], "That": 0, "us": [0, 1, 2, 4, 5, 6, 7, 8, 11, 12, 14, 15, 17, 18], "content": [0, 14], "prior": 0, "ad": [0, 2], "symbol": [0, 5, 7, 10, 16, 17, 19], "from": [0, 1, 2, 5, 9, 15, 16], "base": [0, 8, 11, 12, 14, 18], "posit": 0, "onc": [0, 2, 14, 16], "valu": [0, 1, 2, 4, 5, 6, 7, 10, 14, 15, 16, 17, 19], "sequenti": [0, 12], "all": [0, 2, 4, 5, 7, 14, 19], "avail": [0, 1, 5, 7, 9, 10, 11, 12, 14, 17, 18, 19], "express": [0, 6, 7, 16, 19], "first": [0, 4, 7, 10, 14, 15, 16, 19, 20], "last": [0, 4, 7, 15, 19], "where": [0, 4, 5, 14, 15], "result": [0, 5, 6, 7, 10, 11, 14, 16, 19], "also": [0, 5, 6, 7, 15, 20], "addition": [0, 1, 17, 20], "which": [0, 2, 4, 5, 6, 7, 12, 14, 15, 20], "wa": [0, 16], "ifndef": [0, 1, 2, 3, 4, 5, 6, 7, 10, 14, 15, 16, 17, 18, 19, 20], "lisp16_apply_h": 0, "includ": [0, 1, 2, 3, 4, 5, 6, 7, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20], "env": [0, 3, 7, 16], "lsp_appli": [0, 7, 10], "callabl": [0, 7, 10], "endif": [0, 1, 2, 3, 4, 5, 6, 7, 10, 13, 14, 15, 16, 17, 18, 19, 20], "eval": [0, 6, 10, 16, 19], "write": [0, 1, 9, 10, 11, 16, 17, 18], "static": [0, 1, 2, 4, 5, 6, 7, 11, 12, 14, 15, 16, 18, 20], "create_ctx": 0, "parent_ctx": [0, 4, 14], "arg_nam": 0, "arg_valu": 0, "statu": [0, 2, 5, 6, 7, 10, 11, 13, 14, 15, 16, 18, 19, 20], "lsp_ctx_copi": [0, 5, 19], "m": [0, 1, 2, 3, 4, 5, 6, 7, 10, 13, 14, 15, 16, 18, 19, 20], "lsp_success": [0, 1, 2, 3, 5, 6, 7, 10, 13, 14, 15, 16, 17, 18, 19, 20], "return": [0, 1, 2, 3, 4, 5, 6, 7, 10, 13, 14, 15, 16, 17, 18, 19, 20], "while": [0, 1, 2, 5, 6, 7, 10, 14, 15, 16, 18, 19, 20], "nil": [0, 2, 3, 5, 6, 7, 9, 10, 14, 15, 16, 19, 20], "lsp_mem_is_symbol": [0, 7, 10, 14, 15, 19, 20], "lsp_ctx_add": [0, 5, 19], "break": [0, 5, 14, 15, 20], "lsp_err_arg_count": [0, 3, 10, 16, 17, 19], "lsp_mem_get_pair_first": [0, 3, 5, 7, 10, 14, 19, 20], "lsp_err_arg_typ": [0, 10, 16, 17, 19], "lsp_mem_get_pair_second": [0, 3, 5, 7, 10, 14, 19, 20], "lsp_mem_dec_ref": [0, 2, 5, 6, 7, 10, 13, 14, 15, 16, 19], "apply_builtin_funct": 0, "lsp_uint16_t": [0, 1, 2, 4, 10, 14, 18, 20], "lsp_mem_get_builtin_index": [0, 14, 20], "cb": [0, 3], "lsp_function": [0, 5, 10, 20], "apply_builtin_syntax": 0, "lsp_syntax": [0, 5, 19, 20], "apply_funct": 0, "lsp_mem_get_function_parent_ctx": [0, 14], "lsp_mem_get_function_arg": [0, 14], "lsp_mem_get_function_bodi": [0, 14], "fn_ctx": 0, "lsp_syntax_begin": [0, 19], "apply_syntax": 0, "lsp_mem_get_syntax_parent_ctx": [0, 14], "lsp_mem_get_syntax_arg": [0, 14], "lsp_mem_get_syntax_bodi": [0, 14], "syntax_ctx": 0, "lsp_env_resolv": [0, 6, 7, 16, 19], "lsp_write": [0, 10, 16, 20], "out": [0, 6, 10, 11, 13, 16, 17], "lsp_out_stream_writ": [0, 10, 16, 18, 20], "n": [0, 4, 15, 16], "lsp_env_set_result_ev": [0, 6, 19], "lsp_mem_is_builtin_funct": [0, 7, 10, 14, 20], "lsp_mem_is_builtin_syntax": [0, 10, 14, 20], "lsp_mem_is_funct": [0, 7, 10, 14, 20], "lsp_mem_is_syntax": [0, 10, 14, 20], "lsp_err_appli": [0, 16, 17], "To": [1, 6, 9, 15, 18], "enabl": [1, 4, 5, 6, 12, 14, 15, 18, 20], "easier": [1, 4, 12], "execut": [1, 6, 8, 11, 12, 14, 17], "decoupl": 1, "standard": [1, 11, 15], "librari": [1, 11], "other": [1, 4, 11, 12, 14, 15, 16, 19], "depend": [1, 11, 12], "thin": [1, 12, 14], "requir": [1, 2, 12, 13, 14], "constant": 1, "definit": [1, 4, 5, 19], "lsp_arch": [1, 13], "identifi": [1, 4], "desir": 1, "thi": [1, 4, 5, 6, 7, 9, 11, 12, 14, 16, 17, 18, 19], "should": [1, 9, 11, 12, 14, 16, 19], "set": [1, 4, 9, 10, 19], "preprocess": 1, "one": [1, 4, 10, 12, 14, 15], "lsp_arch_posix": [1, 13], "lsp_arch_avr8": [1, 13], "8bit": [1, 4, 12, 18], "avr": 1, "implement": [1, 4, 5, 6, 8, 9, 11, 12, 13, 16, 18, 19], "defin": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, 17, 18, 19, 20], "fix": 1, "length": [1, 2, 4, 9, 10, 15], "integ": [1, 4, 14, 17, 18], "lsp_int8_t": [1, 17], "lsp_int16_t": [1, 18], "lsp_int32_t": [1, 4, 10, 14, 15, 18], "lsp_uint8_t": [1, 2, 4, 10, 14, 15, 16, 18, 20], "lsp_uint32_t": [1, 4], "independ": [1, 11, 12], "If": [1, 5, 7, 11, 12, 14, 19], "ha": [1, 17], "alias": 1, "stdint": 1, "doesn": [1, 4, 7, 12], "t": [1, 4, 7, 9, 12, 15, 16], "have": [1, 11, 14, 15], "appropri": 1, "char": [1, 3, 14, 18], "short": 1, "int": [1, 13], "long": 1, "lsp_bool_t": [1, 4, 5, 6, 10, 14, 15, 18, 19, 20], "alia": [1, 17], "_bool": 1, "can": [1, 2, 6, 7, 11, 12, 14, 15, 16, 20], "care": 1, "taken": [1, 12], "convers": 1, "so": 1, "could": [1, 14], "respons": [1, 6, 13, 14, 15], "follow": [1, 3, 4, 7, 10, 11, 12, 16, 19], "lsp_arch_init": [1, 13], "befor": [1, 8], "ani": [1, 5, 11], "initi": [1, 2, 5, 13, 14, 18], "state": [1, 6, 14], "lsp_arch_create_mem": [1, 13], "alloc": [1, 5, 11, 12], "memori": [1, 4, 5, 6, 11, 12, 16, 17], "lsp_mem_t": [1, 2, 3, 5, 6, 13, 14, 15, 18, 20], "structur": [1, 3, 7, 12, 13, 14, 15], "": [1, 4, 11, 12, 15, 16, 17, 18, 20], "lsp_arch_free_mem": [1, 13], "free": [1, 11, 14], "lsp_arch_create_in_stream": [1, 13], "lsp_in_stream_t": [1, 6, 13, 15, 16, 18], "lsp_arch_free_in_stream": [1, 13], "lsp_arch_create_out_stream": [1, 13], "lsp_out_stream_t": [1, 6, 13, 16, 18, 20], "lsp_arch_free_out_stream": [1, 13], "constrain": [1, 12, 14], "g": 1, "prealloc": [1, 2, 14], "instead": [1, 4, 5, 12, 14], "dynam": [1, 14], "For": 1, "don": [1, 15], "signatur": 1, "lsp_stream_getchar_t": [1, 18], "read": [1, 2, 10, 12, 16, 17, 18], "singl": [1, 2, 4, 5, 6, 7, 11, 12, 14, 18], "charact": [1, 2, 4, 10, 15, 18, 19, 20], "repl": [1, 11, 12, 13], "behavior": 1, "correspond": [1, 14], "getchar": [1, 11, 18], "detail": [1, 11], "lsp_stream_putchar_t": [1, 18], "v": [1, 4, 15, 18], "putchar": [1, 11, 18], "lisp16_arch_h": 1, "0": [1, 2, 4, 5, 9, 10, 13, 14, 15, 17, 18, 19, 20], "1": [1, 2, 4, 5, 8, 9, 10, 11, 13, 14, 15, 17, 18, 19], "lsp_arch_stm32": [1, 13], "2": [1, 4, 10, 14, 15, 17, 19], "error": [1, 7, 10, 16, 17], "int8_t": 1, "int16_t": 1, "int32_t": 1, "uint8_t": [1, 5], "uint16_t": 1, "uint32_t": 1, "elif": [1, 13], "els": [1, 4, 5, 7, 9, 10, 14, 15, 16, 19, 20], "unknown": [1, 17], "null": [1, 10, 13, 18, 19], "void": [1, 2, 4, 6, 14, 16, 18], "true": [1, 4, 5, 6, 14, 15, 16, 18, 19, 20], "fals": [1, 4, 5, 6, 14, 15, 18, 20], "lisp16_arch_avr8_h": 1, "mem": [1, 2, 5, 6, 15, 18, 20], "lsp_arch_avr8_init": 1, "lsp_arch_avr8_create_mem": 1, "lsp_arch_avr8_free_mem": 1, "lsp_arch_avr8_create_in_stream": 1, "lsp_arch_avr8_free_in_stream": 1, "lsp_arch_avr8_create_out_stream": 1, "lsp_arch_avr8_free_out_stream": 1, "io": 1, "mem_siz": 1, "0x01c0": 1, "uart_baud": 1, "9600": 1, "avr8_getchar": 1, "ucsr0a": 1, "7": [1, 4, 14, 17], "udr0": 1, "avr8_putchar": 1, "5": [1, 14, 17], "avr8_mem": 1, "sizeof": 1, "lsp_cell_t": [1, 4, 14], "avr8_in_stream": 1, "avr8_out_stream": 1, "ubrr0": 1, "f_cpu": 1, "16": [1, 14], "ucsr0b": 1, "_bv": 1, "txen0": 1, "rxen0": 1, "lsp_mem_init": [1, 14], "lsp_in_stream_init": [1, 18], "lsp_out_stream_init": [1, 18], "lisp16_arch_posix_h": 1, "lsp_arch_posix_init": 1, "lsp_arch_posix_create_mem": 1, "lsp_arch_posix_free_mem": 1, "lsp_arch_posix_create_in_stream": 1, "lsp_arch_posix_free_in_stream": 1, "lsp_arch_posix_create_out_stream": 1, "lsp_arch_posix_free_out_stream": 1, "stdio": 1, "stdlib": 1, "0x4000": [1, 4], "posix_getchar": 1, "eof": 1, "lsp_eof": [1, 13, 16, 17, 18], "posix_putchar": 1, "malloc": [1, 11], "input": [2, 6, 10, 11, 14, 15, 16, 19], "stream": [2, 6, 10, 11, 15, 16, 19, 20], "store": 2, "arbitrari": [2, 4, 5, 15], "lsp_buff_t": [2, 15], "limit": [2, 4, 9, 14], "temporari": [2, 14], "storag": [2, 5, 6], "intermediari": 2, "construct": [2, 12, 19], "size": [2, 4, 11, 14, 18], "after": [2, 7, 9, 11, 14], "lsp_buff_init": [2, 15], "lsp_buff_push": [2, 15], "function": [2, 3, 5, 6, 7, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], "append": 2, "obtain": [2, 5], "lsp_buff_pop": [2, 15], "lisp16_buff_h": 2, "lsp_buff_siz": 2, "32": 2, "struct": [2, 3, 6, 14, 18], "buff_len": 2, "b": [2, 4, 15], "lsp_buff_clear": [2, 15], "update_str": 2, "value_len": 2, "lsp_mem_get_string_len": [2, 10, 14, 18, 19, 20], "lsp_mem_create_str": [2, 10, 14], "lsp_mem_set_string_data": [2, 10, 14], "lsp_mem_get_string_data": [2, 10, 14, 18, 20], "syntax": [3, 5, 7, 9, 10, 11, 12, 14, 15, 20], "lsp_builtin_entry_t": [3, 10, 19], "uniqu": 3, "applic": [3, 5, 7, 11, 12, 16, 17], "lisp16_builtin_h": 3, "lsp_builtin_get_args_1": [3, 10, 19], "arg1": 3, "lsp_builtin_get_args_2": [3, 10, 19], "arg2": 3, "lsp_builtin_get_args_3": [3, 10], "arg3": 3, "encod": [4, 15, 17, 20], "more": [4, 9, 11, 12, 15], "consecut": 4, "16bit": [4, 11], "word": [4, 14], "most": [4, 12, 14], "signific": [4, 12, 14, 15], "bit": [4, 14], "reserv": 4, "manag": [4, 11], "usag": [4, 5, 12], "remain": [4, 7, 14], "15bit": 4, "referenc": [4, 5, 12, 14], "15": 4, "least": 4, "mostli": [4, 5, 11, 12], "inlin": [4, 14, 15], "header": 4, "file": [4, 17], "preprocessor": 4, "api": [4, 11, 12], "suitabl": [4, 12], "foreign": [4, 11, 12], "interfac": [4, 11, 12, 14], "sign": [4, 18], "although": [4, 12], "manipul": [4, 14], "32bit": [4, 12], "dual": 4, "complement": 4, "address": [4, 14], "14": 4, "13": 4, "12": 4, "rest": [4, 9, 12, 15], "two": 4, "locat": [4, 12], "usual": [4, 12, 17], "known": [4, 5, 6], "con": [4, 9, 10], "14bit": [4, 14], "unsign": [4, 14, 18], "10": [4, 8, 9, 14, 15, 17, 18], "second": [4, 10, 14, 15, 19, 20], "zero": [4, 10, 14, 15], "d": 4, "11": 4, "1100": 4, "maximum": [4, 15], "2047": [4, 15], "schema": 4, "tri": [4, 12], "optim": [4, 5, 6, 11, 14], "same": [4, 12, 14, 20], "time": [4, 12, 14], "introduc": [4, 5, 15], "overhead": [4, 5], "human": 4, "readabl": 4, "label": 4, "similarli": 4, "1101": 4, "11100": 4, "11101": 4, "addresse": 4, "within": 4, "4": [4, 14, 15, 17], "x": [4, 8, 9, 17, 19], "3": [4, 11, 15, 17, 19], "11110": 4, "lisp16_cell_h": 4, "arch": [4, 13, 17], "lsp_cell_get_s": [4, 14], "lsp_cell_get_number_s": [4, 14], "lsp_cell_get_string_symbol_s": [4, 14], "len": [4, 9, 20], "lsp_cell_is_numb": [4, 14], "0x0000": 4, "lsp_cell_is_pair": [4, 14], "0x6000": 4, "lsp_cell_is_str": [4, 14], "0x7800": 4, "lsp_cell_is_symbol": [4, 14], "0x6800": 4, "lsp_cell_is_builtin_funct": [4, 14], "0x7c00": 4, "0x7000": 4, "lsp_cell_is_builtin_syntax": [4, 14], "0x7400": 4, "lsp_cell_is_funct": [4, 14], "lsp_cell_is_syntax": [4, 14], "lsp_cell_is_string_or_symbol": [4, 14], "lsp_cell_is_builtin": [4, 14], "lsp_cell_is_function_or_syntax": [4, 14], "lsp_cell_set_numb": [4, 14], "shift": 4, "0x3fff": 4, "0x1fff": 4, "0x2000": 4, "lsp_cell_set_pair": [4, 14], "lsp_cell_set_str": [4, 14], "data_len": [4, 14], "0x07ff": 4, "lsp_cell_set_string_data": [4, 14], "data_i": [4, 14], "bit_count": 4, "start_cel": 4, "bit_shift": 4, "mask": 4, "0x7f80": 4, "8": [4, 17], "22": 4, "0xffff": 4, "0x7fff": [4, 14], "lsp_cell_set_symbol": [4, 14], "name_len": [4, 14], "lsp_cell_set_symbol_nam": [4, 14], "name_i": 4, "lsp_cell_set_builtin_funct": [4, 14], "0x03ff": 4, "lsp_cell_set_builtin_syntax": [4, 14], "lsp_cell_set_funct": [4, 14], "lsp_cell_set_syntax": [4, 14], "lsp_cell_get_numb": [4, 14], "0x1000": 4, "0x0fff": 4, "lsp_cell_get_pair_first": [4, 14], "lsp_cell_get_pair_second": [4, 14], "lsp_cell_get_string_len": [4, 14], "lsp_cell_get_string_data": [4, 14], "start_bit": 4, "0xff": 4, "lsp_cell_get_symbol_len": [4, 14], "lsp_cell_get_symbol_nam": [4, 14], "lsp_cell_get_builtin_index": [4, 14], "lsp_cell_get_function_parent_ctx": [4, 14], "lsp_cell_get_function_arg": [4, 14], "lsp_cell_get_function_bodi": [4, 14], "lsp_cell_get_syntax_parent_ctx": [4, 14], "lsp_cell_get_syntax_arg": [4, 14], "lsp_cell_get_syntax_bodi": [4, 14], "msb": 4, "environ": [5, 9, 11, 12], "some": [5, 12, 15], "lisp": [5, 7, 9, 11, 12, 15, 19], "appli": [5, 7, 9, 10, 20], "specif": [5, 12, 14, 18], "scope": [5, 11], "lexic": 5, "regard": [5, 18], "namespac": [5, 11], "basic": [5, 18], "method": [5, 6], "exact": 5, "current": [5, 6, 7, 14, 19], "moment": 5, "inherit": 5, "were": 5, "start": [5, 10, 11, 14, 15, 19], "builtin": [5, 7, 9, 11, 12, 15, 17, 20], "mutabl": 5, "kind": [5, 11, 12], "add": [5, 14, 19], "lsp_ctx_get": [5, 7], "modif": [5, 14], "lsp_ctx_set": [5, 19], "instanc": [5, 6, 7, 11, 12, 14, 15], "chang": [5, 14, 19], "modifi": [5, 11, 14], "point": 5, "newli": [5, 14], "child": 5, "exist": [5, 12, 14], "visibl": 5, "becaus": [5, 7, 12, 14], "support": [5, 11, 12], "tail": [5, 6, 11], "hierarchi": 5, "reli": [5, 12], "oper": 5, "induc": [5, 12], "addit": [5, 9, 12, 14], "never": 5, "less": 5, "neutral": 5, "immut": [5, 14], "link": 5, "basi": 5, "lisp16_ctx_h": 5, "lsp_ctx_creat": [5, 13], "contains_symbol": 5, "entry_symbol": 5, "lsp_mem_eq": [5, 10, 14], "remove_symbol": 5, "result_last": 5, "lsp_mem_inc_ref": [5, 6, 7, 14], "lsp_mem_set_pair_second": [5, 7, 10, 14, 15], "new_result_last": 5, "lsp_mem_create_pair": [5, 7, 10, 14, 15], "lsp_mem_set_pair_first": [5, 10, 14], "list_last": 5, "lsp_mem_create_symbol_from_char": [5, 14], "lsp_mem_create_builtin_syntax": [5, 14], "new_list_last": 5, "lsp_mem_create_builtin_funct": [5, 14], "lsp_err_ctx": [5, 16, 17], "mix": 6, "interpret": [6, 7, 8, 9, 11, 12, 14, 15, 16, 18], "It": [6, 12, 14, 18], "output": [6, 10, 11, 16, 19, 20], "next": [6, 18], "main": [6, 11], "loop": [6, 16], "trampolin": 6, "iter": 6, "sequenc": [6, 15, 18], "direct": [6, 14], "regist": 6, "lsp_env_set_result_valu": [6, 7, 10, 19], "deleg": [6, 7], "anoth": 6, "repeat": [6, 14], "until": [6, 15], "fulli": 6, "resolv": [6, 16], "lisp16_env_h": 6, "intern": [6, 14, 18], "is_valu": 6, "lsp_env_init": [6, 13], "init_result": 6, "release_result": 6, "eval_ctx": 6, "eval_valu": 6, "lsp_eval": [6, 7, 10], "instruct": [7, 9, 12, 15], "when": [7, 9], "accord": 7, "string": [7, 9, 10, 11, 14, 18, 20], "consist": 7, "signal": 7, "pair": [7, 9, 10, 14], "step": [7, 14, 16], "element": [7, 15], "possibl": [7, 11, 14], "except": [7, 14], "rule": [7, 20], "empti": [7, 15, 19], "lisp16_eval_h": 7, "eval_arg": 7, "goto": [7, 13, 15], "new_last": [7, 15], "lsp_mem_is_numb": [7, 10, 14, 19, 20], "lsp_mem_is_str": [7, 10, 14, 19, 20], "lsp_mem_is_builtin": [7, 10, 14], "lsp_mem_is_function_or_syntax": [7, 10, 14], "lsp_mem_is_pair": [7, 10, 14, 19, 20], "lsp_err_ev": [7, 16, 17], "run": [8, 11, 12], "build": 8, "posix": [8, 12, 13], "platform": [8, 11, 12, 14, 18], "bootstrap": [8, 9], "larg": 8, "lsp": 8, "extens": [8, 11], "simpl": [8, 11, 12, 14], "calcul": 8, "cat": 8, "src_lsp": 8, "lisp16": 8, "3628800": 8, "languag": [9, 12, 15], "deliber": 9, "design": [9, 11, 12, 14], "usabl": [9, 12, 14], "develop": [9, 12], "written": [9, 10, 11, 15, 16, 19, 20], "These": [9, 14, 15], "immedi": [9, 14], "startup": 9, "finish": [9, 14, 16], "part": [9, 11, 12, 14], "activ": 9, "f": 9, "lambda": [9, 19], "car": [9, 10], "cdr": [9, 10], "head": 9, "begin": [9, 15, 17, 19], "cadr": 9, "caar": 9, "cdar": 9, "cadar": 9, "eq": [9, 10], "test": [9, 11, 12, 19], "cond": 9, "let": 9, "bind": [9, 19], "newlin": 9, "u8": [9, 10], "str": [9, 10, 14, 15, 18], "ref": [9, 10], "exampl": [10, 11, 15, 19], "line": [10, 11, 15, 19], "equal": 10, "peek": 10, "make": 10, "lisp16_function_h": 10, "extern": [10, 19], "lsp_function_ev": 10, "lsp_function_appli": 10, "lsp_function_error": 10, "lsp_function_con": 10, "lsp_function_set_car": 10, "lsp_function_set_cdr": 10, "lsp_function_is_numb": 10, "lsp_function_is_pair": 10, "lsp_function_is_str": 10, "lsp_function_is_symbol": 10, "lsp_function_is_funct": 10, "lsp_function_is_syntax": 10, "lsp_function_eq": 10, "lsp_function_equ": 10, "lsp_function_gt": 10, "lsp_function_lt": 10, "lsp_function_plu": 10, "lsp_function_minu": 10, "lsp_function_multipli": 10, "lsp_function_divid": 10, "lsp_function_read": 10, "lsp_function_read_u8": 10, "lsp_function_peek_u8": 10, "lsp_function_writ": 10, "lsp_function_write_u8": 10, "lsp_function_make_str": 10, "lsp_function_string_length": 10, "lsp_function_string_ref": 10, "lsp_function_string_set": 10, "lsp_mem_get_numb": [10, 14, 19, 20], "126": [10, 17], "lsp_err_arg_valu": [10, 16, 17], "lsp_err_us": [10, 16, 17], "is_numb": 10, "is_pair": 10, "is_str": 10, "is_symbol": 10, "is_funct": 10, "is_syntax": 10, "is_eq": 10, "is_equ": 10, "lsp_mem_equ": [10, 14], "last_valu": 10, "lsp_mem_create_numb": [10, 14, 15], "counter": 10, "lsp_read": [10, 15, 16], "lsp_in_stream_read": [10, 15, 16, 18], "lsp_in_stream_peek": [10, 15, 18], "str_len": [10, 14], "cross": 11, "http": 11, "kopic": 11, "xyz": [11, 19], "git": 11, "repositori": 11, "github": 11, "com": 11, "bozokop": 11, "project": [11, 12, 14, 17], "intend": 11, "studi": 11, "featur": 11, "compat": 11, "architectur": [11, 18], "small": 11, "layer": [11, 12, 18], "reduc": [11, 12], "dialect": [11, 12], "scheme": [11, 12], "macro": 11, "tree": 11, "walk": 11, "multipl": [11, 12, 19], "process": [11, 12], "mark": [11, 14], "sweep": [11, 14], "garbag": 11, "collect": [11, 14], "take": [11, 12], "account": [11, 12], "educ": [11, 12], "purpos": [11, 12], "emphasi": [11, 12], "sourc": [11, 12], "code": [11, 12], "organ": [11, 12], "over": 11, "binari": 11, "accompani": 11, "explan": [11, 12], "consid": [11, 14], "real": 11, "life": 11, "product": 11, "speed": [11, 12], "virtual": 11, "machin": 11, "compil": 11, "rich": 11, "target": [11, 12], "atmega328p": 11, "gcc": 11, "binutil": 11, "shell": 11, "script": 11, "avr8": [11, 13], "sh": 11, "produc": [11, 15], "bin": 11, "flash": 11, "uart": [11, 12], "port": 11, "c": [11, 12], "musl": 11, "default": 11, "replac": 11, "need": [11, 17, 18], "stdin": 11, "stdout": 11, "python": 11, "sphinx": 11, "furo": 11, "modul": [11, 14], "doc": 11, "folder": 11, "copyright": 11, "2022": 11, "bozo": 11, "program": [11, 12, 15], "softwar": 11, "you": 11, "redistribut": 11, "under": 11, "term": 11, "gnu": 11, "gener": [11, 12, 17], "public": 11, "publish": 11, "foundat": 11, "either": 11, "version": 11, "your": 11, "option": 11, "later": 11, "distribut": 11, "hope": 11, "warranti": 11, "even": [11, 12, 14], "impli": 11, "merchant": 11, "fit": 11, "FOR": 11, "A": 11, "particular": 11, "see": 11, "receiv": 11, "along": 11, "www": 11, "org": 11, "introduct": 11, "abstract": [11, 12, 18], "buffer": [11, 18], "reader": [11, 12, 16, 17, 20], "writer": [11, 16, 17], "modern": 12, "microcontrol": 12, "power": 12, "comput": 12, "form": [12, 15], "afford": 12, "wide": [12, 17], "integr": 12, "circuit": 12, "packag": 12, "perform": 12, "often": [12, 14], "than": 12, "enough": 12, "complex": [12, 15], "algorithm": 12, "constraint": 12, "challeng": 12, "certain": 12, "high": 12, "level": 12, "amount": 12, "ram": 12, "factor": 12, "explor": 12, "similar": 12, "impact": 12, "capabl": 12, "interact": [12, 14, 18], "famili": 12, "character": 12, "concis": [12, 15], "homoicon": 12, "few": [12, 15], "core": 12, "extend": 12, "varieti": 12, "deriv": 12, "paradigm": 12, "domain": 12, "therefor": [12, 15], "good": 12, "system": [12, 14], "embed": 12, "One": 12, "characterist": 12, "we": 12, "rang": [12, 17], "o": 12, "peripher": 12, "exploratori": 12, "low": 12, "peripheri": 12, "split": 12, "commun": 12, "approach": 12, "By": 12, "whole": 12, "self": 12, "suffici": 12, "full": 12, "duplex": 12, "wai": 12, "termin": [12, 18], "those": [12, 14], "util": [12, 18], "lot": 12, "necessari": 12, "host": 12, "friendli": 12, "decis": 12, "notabl": 12, "indirect": 12, "penalti": 12, "motiv": 12, "research": 12, "reason": 12, "given": 12, "document": 12, "explain": 12, "gradual": 12, "bottom": 12, "up": 12, "advis": 12, "order": 12, "close": [12, 16], "its": 12, "knowledg": 12, "relat": 12, "model": 12, "assum": 12, "h": 13, "stm32": 13, "lsp_err": [13, 14, 17], "cleanup": [13, 15], "lsp_repl": [13, 16], "declar": 14, "through": 14, "continu": [14, 15, 16], "block": 14, "count": [14, 16, 17], "16384": 14, "32768": 14, "byte": 14, "smaller": 14, "event": 14, "dedic": 14, "unus": 14, "search": 14, "found": 14, "procedur": 14, "trigger": 14, "success": [14, 17], "fail": 14, "rememb": 14, "futur": 14, "lsp_mem_create_": 14, "access": 14, "root": 14, "increas": 14, "decreas": 14, "reclaim": 14, "quot": [14, 15, 19], "quasiquot": [14, 15], "unquot": [14, 15], "unquote_spl": [14, 15], "variant": 14, "non": 14, "pool": 14, "deplet": 14, "Then": 14, "recurs": [14, 15], "directli": 14, "indirectli": 14, "lsp_mem_is_": 14, "assert": 14, "lsp_mem_get_": 14, "retriev": 14, "wrapper": 14, "cell": 14, "map": 14, "mutat": 14, "afterward": 14, "lsp_mem_set_": 14, "place": 14, "lsp_mem_": 14, "lsp_cell_": 14, "done": 14, "alreadi": 14, "increment": 14, "come": 14, "cost": 14, "sinc": 14, "control": 14, "decrement": 14, "explicitli": 14, "specifi": [14, 15], "otherwis": 14, "caller": 14, "owner": 14, "borrow": 14, "pass": 14, "releas": 14, "lisp16_mem_h": 14, "last_addr": 14, "addr": [14, 15, 20], "lsp_mem_create_symbol_from_str": [14, 15], "lsp_mem_create_funct": [14, 19], "lsp_mem_create_syntax": [14, 19], "a1": 14, "a2": 14, "lsp_mem_is_string_or_symbol": 14, "lsp_mem_get_symbol_len": [14, 15, 19, 20], "lsp_mem_get_symbol_nam": [14, 15, 20], "get_mark": 14, "0x8000": 14, "set_mark": 14, "restor": 14, "c_size": 14, "mark_and_restor": 14, "is_free_cel": 14, "used_addr": 14, "find_free_cel": 14, "lsp_err_mem": [14, 16, 17], "find_free_cell_with_gc": 14, "alloc_cel": 14, "is_symbol_from_str": 14, "is_symbol_from_char": 14, "find_symbol_from_str": 14, "find_symbol_from_char": 14, "splice": 14, "curr_addr": 14, "prev_addr": 14, "a1_len": 14, "a2_len": 14, "parser": 15, "comment": 15, "spawn": 15, "end": [15, 17], "white": 15, "space": 15, "r": 15, "ignor": 15, "delimit": 15, "decim": 15, "9": [15, 17], "detect": [15, 16], "valid": 15, "42": [15, 19], "enclos": 15, "escap": 15, "abc": 15, "123": 15, "par": 15, "nest": 15, "el_1": 15, "el_2": 15, "el_n": 15, "special": [15, 17], "recogn": 15, "do": [15, 16], "conveni": 15, "equival": 15, "lisp16_read_h": 15, "buff": 15, "is_w": 15, "is_comment_start": 15, "is_comment_stop": 15, "is_digit": 15, "is_list_start": 15, "is_list_stop": 15, "is_str_start_stop": 15, "is_quot": 15, "is_quasiquot": 15, "is_unquot": 15, "skip_w": 15, "read_numb": 15, "lsp_err_read": [15, 16, 17], "read_list": 15, "list_end": 15, "read_rest": 15, "read_stop": 15, "el": 15, "read_str": 15, "read_escap": 15, "read_quot": 15, "read_quasiquot": 15, "read_unquot": 15, "is_splic": 15, "read_symbol": 15, "suggest": 16, "endless": 16, "action": 16, "print": 16, "skip": 16, "stop": 16, "lisp16_repl_h": 16, "log_statu": 16, "lsp_out_stream_write_str": [16, 18, 20], "lsp_err_writ": [16, 17, 20], "invalid": [16, 17], "user": [16, 17, 19], "lsp_out_stream_write_int": [16, 18, 20], "skip_lin": 16, "adopt": 17, "convent": 17, "notifi": 17, "encount": 17, "resolut": 17, "abil": 17, "rais": 17, "lsp_status_h": 17, "lsp_statu": 17, "6": 17, "0x80": 17, "lisp16_stream_h": 18, "next_avail": 18, "next_valu": 18, "next_statu": 18, "po": 18, "lsp_str_stream_t": 18, "lsp_str_stream_init": 18, "str_getchar": 18, "ss": 18, "temp": 18, "j": 18, "digit": 18, "minim": 19, "y": 19, "24": 19, "thruthi": 19, "falsi": 19, "third": 19, "lisp16_syntax_h": 19, "lsp_syntax_lambda": 19, "lsp_syntax_syntax": 19, "lsp_syntax_defin": 19, "lsp_syntax_set": 19, "lsp_syntax_quot": 19, "lsp_syntax_if": 19, "fn_arg": 19, "fn_bodi": 19, "ctx_copi": 19, "syntax_arg": 19, "syntax_bodi": 19, "next_arg": 19, "true_valu": 19, "false_valu": 19, "is_fals": 19, "serial": 20, "inform": 20, "pars": 20, "lisp16_write_h": 20, "write_numb": 20, "write_pair": 20, "write_spac": 20, "write_str": 20, "write_symbol": 20, "write_builtin_funct": 20, "write_builtin_syntax": 20, "write_funct": 20, "write_syntax": 20}, "objects": {}, "objtypes": {}, "objnames": {}, "titleterms": {"function": [0, 1, 4, 10], "syntax": [0, 4, 19], "applic": 0, "builtin": [0, 3, 4, 10, 19], "user": 0, "defin": 0, "sourc": [0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 13, 14, 15, 16, 17, 18, 19, 20], "code": [0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 13, 14, 15, 16, 17, 18, 19, 20], "appli": 0, "h": [0, 1, 2, 3, 4, 5, 6, 7, 10, 14, 15, 16, 17, 18, 19, 20], "c": [0, 1, 2, 3, 4, 5, 6, 7, 10, 13, 14, 15, 16, 18, 19, 20], "architectur": 1, "abstract": 1, "layer": 1, "support": 1, "target": 1, "platform": 1, "data": [1, 4, 14, 15, 20], "type": [1, 4], "specif": 1, "input": [1, 18], "stream": [1, 18], "output": [1, 18], "arch": 1, "avr8": 1, "posix": [1, 11], "string": [2, 4, 15], "buffer": 2, "buff": 2, "number": [4, 15], "pair": [4, 15], "symbol": [4, 14, 15], "cell": 4, "context": 5, "ctx": 5, "environ": 6, "env": 6, "evalu": 7, "eval": 7, "exampl": 8, "factori": 8, "extens": 9, "base": 9, "small": 9, "lsp": 9, "larg": 9, "lisp16": 11, "about": 11, "build": 11, "usag": [11, 14], "8bit": 11, "avr": 11, "microcontrol": 11, "system": 11, "document": 11, "licens": 11, "content": 11, "introduct": 12, "main": 13, "memori": 14, "manag": 14, "layout": 14, "alloc": 14, "garbag": 14, "collector": 14, "reusabl": 14, "ownership": 14, "convent": 14, "mem": 14, "reader": 15, "list": 15, "macro": 15, "read": 15, "repl": 16, "result": 17, "statu": 17, "writer": 20, "write": 20}, "envversion": {"sphinx.domains.c": 2, "sphinx.domains.changeset": 1, "sphinx.domains.citation": 1, "sphinx.domains.cpp": 8, "sphinx.domains.index": 1, "sphinx.domains.javascript": 2, "sphinx.domains.math": 2, "sphinx.domains.python": 3, "sphinx.domains.rst": 2, "sphinx.domains.std": 2, "sphinx.ext.todo": 2, "sphinx": 57}, "alltitles": {"Function/syntax application": [[0, "function-syntax-application"]], "Builtin function/syntax application": [[0, "builtin-function-syntax-application"]], "User defined function/syntax application": [[0, "user-defined-function-syntax-application"]], "Source code": [[0, "source-code"], [1, "source-code"], [2, "source-code"], [3, "source-code"], [4, "source-code"], [5, "source-code"], [6, "source-code"], [7, "source-code"], [9, "source-code"], [10, "source-code"], [13, "source-code"], [14, "source-code"], [15, "source-code"], [16, "source-code"], [17, "source-code"], [18, "source-code"], [19, "source-code"], [20, "source-code"]], "apply.h": [[0, "apply-h"]], "apply.c": [[0, "apply-c"]], "Architecture abstraction layer": [[1, "architecture-abstraction-layer"]], "Supported target platforms": [[1, "supported-target-platforms"]], "C data types": [[1, "c-data-types"]], "Platform specific functions": [[1, "platform-specific-functions"]], "Input stream": [[1, "input-stream"], [18, "input-stream"]], "Output stream": [[1, "output-stream"], [18, "output-stream"]], "arch.h": [[1, "arch-h"]], "arch/avr8.h": [[1, "arch-avr8-h"]], "arch/avr8.c": [[1, "arch-avr8-c"]], "arch/posix.h": [[1, "arch-posix-h"]], "arch/posix.c": [[1, "arch-posix-c"]], "String buffer": [[2, "string-buffer"]], "buff.h": [[2, "buff-h"]], "buff.c": [[2, "buff-c"]], "Builtin": [[3, "builtin"]], "builtin.h": [[3, "builtin-h"]], "builtin.c": [[3, "builtin-c"]], "Data types": [[4, "data-types"]], "Number": [[4, "number"], [15, "number"]], "Pair": [[4, "pair"]], "String": [[4, "string"], [15, "string"]], "Symbol": [[4, "symbol"], [15, "symbol"]], "Builtin function": [[4, "builtin-function"]], "Builtin syntax": [[4, "builtin-syntax"]], "Function": [[4, "function"]], "Syntax": [[4, "syntax"]], "cell.h": [[4, "cell-h"]], "cell.c": [[4, "cell-c"]], "Context": [[5, "context"]], "ctx.h": [[5, "ctx-h"]], "ctx.c": [[5, "ctx-c"]], "Environment": [[6, "environment"]], "env.h": [[6, "env-h"]], "env.c": [[6, "env-c"]], "Evaluation": [[7, "evaluation"]], "eval.h": [[7, "eval-h"]], "eval.c": [[7, "eval-c"]], "Examples": [[8, "examples"]], "Factorial": [[8, "factorial"]], "Extensions": [[9, "extensions"]], "base-small.lsp": [[9, "base-small-lsp"]], "base-large.lsp": [[9, "base-large-lsp"]], "Builtin functions": [[10, "builtin-functions"]], "function.h": [[10, "function-h"]], "function.c": [[10, "function-c"]], "lisp16": [[11, "lisp16"]], "About": [[11, "about"]], "Building and usage": [[11, "building-and-usage"]], "8bit AVR microcontrollers": [[11, "bit-avr-microcontrollers"]], "POSIX system": [[11, "posix-system"]], "Documentation": [[11, "documentation"]], "License": [[11, "license"]], "Content": [[11, "content"]], "Introduction": [[12, "introduction"]], "Main": [[13, "main"]], "main.c": [[13, "main-c"]], "Memory management": [[14, "memory-management"]], "Memory layout": [[14, "memory-layout"]], "Data allocation": [[14, "data-allocation"]], "Garbage collector": [[14, "garbage-collector"]], "Data usage": [[14, "data-usage"]], "Symbol reusability": [[14, "symbol-reusability"]], "Ownership conventions": [[14, "ownership-conventions"]], "mem.h": [[14, "mem-h"]], "mem.c": [[14, "mem-c"]], "Data reader": [[15, "data-reader"]], "Pair/list": [[15, "pair-list"]], "Reader macros": [[15, "reader-macros"]], "read.h": [[15, "read-h"]], "read.c": [[15, "read-c"]], "REPL": [[16, "repl"]], "repl.h": [[16, "repl-h"]], "repl.c": [[16, "repl-c"]], "Result status codes": [[17, "result-status-codes"]], "status.h": [[17, "status-h"]], "Input/output stream": [[18, "input-output-stream"]], "stream.h": [[18, "stream-h"]], "stream.c": [[18, "stream-c"]], "Builtin syntaxes": [[19, "builtin-syntaxes"]], "syntax.h": [[19, "syntax-h"]], "syntax.c": [[19, "syntax-c"]], "Data writer": [[20, "data-writer"]], "write.h": [[20, "write-h"]], "write.c": [[20, "write-c"]]}, "indexentries": {}})