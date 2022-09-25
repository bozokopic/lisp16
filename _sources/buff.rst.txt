String buffer
=============

While reading character data from input stream, buffer used for storing
string of arbitrary length is required. `lsp_buff_t` provides preallocated
limited temporary storage which is used as intermediary buffer in construction
of `string` data with arbitrary size.

After initialization with `lsp_buff_init`, characters are added to buffer
with `lsp_buff_push` function. Once all characters are appended, single
`string` data containing all previously appended characters, can be obtained
with `lsp_buff_pop` function.


Source code
-----------

buff.h
''''''

.. literalinclude:: ../src_c/buff.h
    :language: c


buff.c
''''''

.. literalinclude:: ../src_c/buff.c
    :language: c
