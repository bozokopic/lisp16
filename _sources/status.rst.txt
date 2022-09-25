Result status codes
===================

This project adopts widely used convention of returning integer encoded status
codes as function results.

Each function, that needs to notify it's execution status (success or error),
returns ``lsp_status_t`` (alias for ``lsp_int8_t``).

Available status codes are:

    * ``LSP_SUCCESS``

        Execution successful.

    * ``LSP_EOF``

        End of file encountered during reading/writing.

    * ``LSP_ERR``

        Generic error (unknown error).

    * ``LSP_ERR_MEM``

        Memory error (usually out of memory).

    * ``LSP_ERR_CTX``

        Context error (usually symbol resolution error).

    * ``LSP_ERR_READ``

        Reader error.

    * ``LSP_ERR_WRITE``

        Writer error.

    * ``LSP_ERR_EVAL``

        Evaluation error.

    * ``LSP_ERR_APPLY``

        Application error.

    * ``LSP_ERR_ARG_COUNT``

        Invalid argument count.

    * ``LSP_ERR_ARG_TYPE``

        Invalid argument type.

    * ``LSP_ERR_ARG_VALUE``

        Invalid argument value.

    * ``LSP_ERR_USER``

        Special status value representing beginning of user status codes.

User has ability to raise user error with ``error`` builtin function. This
error is additionally described with integer value in range [0, 126] and
encoded as status code.


Source code
-----------

status.h
''''''''

.. literalinclude:: ../src_c/status.h
    :language: c
