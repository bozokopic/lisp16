Architecture abstraction layer
==============================

To enable easier targeting of different execution platforms and provide
decoupling from standard C library (or other dependencies), thin abstraction
layer is required.


Supported target platforms
--------------------------

Constant definition ``LSP_ARCH`` is used as identifier of desired target
platform. This definition should be set during C source preprocessing to
one of supported values:

    * ``LSP_ARCH_POSIX`` (POSIX target)
    * ``LSP_ARCH_AVR8`` (8bit AVR target)

Depending on value of this constant, different platform specific
implementations will be included.


C data types
------------

`arch.h` defines fixed length integers (``lsp_int8_t``, ``lsp_int16_t``,
``lsp_int32_t``, ``lsp_uint8_t``, ``lsp_uint16_t``, ``lsp_uint32_t``)
independent of target platform. If target has available standard C library,
this types are aliases to types defined by `stdint.h`. In case target doesn't
have standard C library available, these types should be defined by
appropriate C integer types (``char``, ``short``, ``int``, ``long``, ...).

Additionally, ``lsp_bool_t`` is defined as alias to ``_Bool``. If ``_Bool``
type is not available, ``lsp_uint8_t`` can be used. Care is taken not to depend
on specifics of integer to ``_Bool`` conversions so that other integer types
could be used as ``lsp_bool_t``.


Platform specific functions
---------------------------

Each platform abstraction layer implementation (`arch/*.c`) is responsible
for functions aliased with following names:

    * ``LSP_ARCH_INIT``

        Function, called before any other function, responsible for
        initialization of platform specific state.

    * ``LSP_ARCH_CREATE_MEM``

        Function responsible for allocating memory that will represent
        ``lsp_mem_t`` structure (described in following chapters) and it's
        initialization.

    * ``LSP_ARCH_FREE_MEM``

        Function responsible for freeing previously allocated memory.

    * ``LSP_ARCH_CREATE_IN_STREAM``

        Function responsible for allocating memory that will represent
        ``lsp_in_stream_t`` structure (described in following chapters) and
        it's initialization.

    * ``LSP_ARCH_FREE_IN_STREAM``

        Function responsible for freeing previously allocated memory.

    * ``LSP_ARCH_CREATE_OUT_STREAM``

        Function responsible for allocating memory that will represent
        ``lsp_out_stream_t`` structure (described in following chapters) and
        it's initialization.

    * ``LSP_ARCH_FREE_OUT_STREAM``

        Function responsible for freeing previously allocated memory.

In case of memory constrained targets (e.g. ``LSP_ARCH_AVR8``), functions 
responsible for allocating memory can return pointers to statically
preallocated memory instead of dynamically allocated. For this target
platforms, associated freeing functions don't implement any functionality.


Input stream
------------

During initialization of input stream, platform specific implementation
is responsible for providing function pointer with signature:

.. code-block:: c

    typedef lsp_int16_t (*lsp_stream_getchar_t)(lsp_in_stream_t *s);

Provided function is responsible for reading single character from input
stream (used by REPL). In case of POSIX, it's behavior corresponds to
``getchar`` provided by standard C library.

Details of input stream implementation are available in following chapters.


Output stream
-------------

During initialization of output stream, platform specific implementation
is responsible for providing function pointer with signature:

.. code-block:: c

    typedef lsp_int16_t (*lsp_stream_putchar_t)(lsp_out_stream_t *s, lsp_int16_t v);

Provided function is responsible for writing single character to output
stream (used by REPL). In case of POSIX, it's behavior corresponds to
``putchar`` provided by standard C library.

Details of output stream implementation are available in following chapters.


Source code
-----------

arch.h
''''''

.. literalinclude:: ../src_c/arch.h
    :language: c


arch/avr8.h
'''''''''''

.. literalinclude:: ../src_c/arch/avr8.h
    :language: c


arch/avr8.c
'''''''''''

.. literalinclude:: ../src_c/arch/avr8.c
    :language: c


arch/posix.h
''''''''''''

.. literalinclude:: ../src_c/arch/posix.h
    :language: c


arch/posix.c
''''''''''''

.. literalinclude:: ../src_c/arch/posix.c
    :language: c
