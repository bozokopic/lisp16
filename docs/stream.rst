Input/output stream
===================

To enable interaction with interpreter, basic input/output stream abstraction
is needed. This implementation uses platform specific functions defined
by architecture abstraction layer.


Input stream
------------

Input stream provides functionality of reading unsigned 8bit integers
representing input characters. Implementation utilized `lsp_stream_getchar_t`
function pointer provided during input stream initialization. Together with
`lsp_in_stream_read`, used for reading next available input character, input
stream contains single character buffer used for implementation of
`lsp_in_stream_peek` functionality.


Output stream
-------------

Output stream provides functionality regarding writing character data.
It uses `lsp_stream_putchar_t` function pointer provided during output stream
initialization. Available functions include:

    * `lsp_out_stream_write`

        Write single character to output stream.

    * `lsp_out_stream_write_str`

        Write null terminated character sequence.

    * `lsp_out_stream_write_int`

        Write string representation of signed integer.


Source code
-----------

stream.h
''''''''

.. literalinclude:: ../src_c/stream.h
    :language: c


stream.c
''''''''

.. literalinclude:: ../src_c/stream.c
    :language: c
