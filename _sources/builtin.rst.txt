Builtin
=======

Builtin functions and builtin syntaxes are represented with
`lsp_builtin_entry_t` structures. Each entry is defined with unique
name and function pointer:

.. code-block:: c

    typedef lsp_status_t (*lsp_builtin_cb_t)(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);

Associated function pointer is called during function/syntax application
(described in following chapters).


Source code
-----------

builtin.h
'''''''''

.. literalinclude:: ../src_c/builtin.h
    :language: c


builtin.c
'''''''''

.. literalinclude:: ../src_c/builtin.c
    :language: c
