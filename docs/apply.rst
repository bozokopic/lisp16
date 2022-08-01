Function/syntax application
===========================

Builtin function/syntax application
-----------------------------------

Data representing builtin function/syntax, together with type identification,
contains number representing index of builtin entry. As described in previous
chapters, each builtin entry contains function pointer:

.. code-block:: c

    typedef lsp_status_t (*lsp_builtin_cb_t)(lsp_env_t *e, lsp_addr_t ctx, lsp_addr_t args);

Application of builtin function/syntax calls provided native function
with arguments provided to function/syntax application.

Only difference between builtin function and syntax application is in arguments
provided to application itself. In case of function application, these
arguments are previously evaluated and in case of syntax, they are provided
without previous evaluation.


User defined function/syntax application
----------------------------------------

Data representation of function/syntax references:

    * parent context
    * argument name list
    * function/syntax body

During function/syntax application, new context is created as copy of
associated parent context. That context is used for evaluation of
function/syntax content. Prior to content evaluation, provided arguments
are added as new entries in context and are associated with symbols
from argument name list based on their position in list. Once context
is created and argument values are associated, function/syntax body is
evaluated. Evaluation of function/syntax body is sequential evaluation
of all available expression (from first to last) where value of last expression
is used as resulting value.

In case of function application, result of last expression evaluation is
also value of function application itself. In case of syntax evaluation,
result of last expression is data that is additionally evaluated in context
from which syntax application was called.


Source code
-----------

apply.h
'''''''

.. literalinclude:: ../src_c/apply.h
    :language: c


apply.c
'''''''

.. literalinclude:: ../src_c/apply.c
    :language: c
