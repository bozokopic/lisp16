Environment
===========

Environment (not to be mixed with context) represent current state of
interpreter instance. It contains reference to memory, input stream and
output stream. To enable
`tail call optimization <https://en.wikipedia.org/wiki/Tail_call>`_,
environment is also used as storage for next expression evaluation.

Main method responsible for environment evaluation is `lsp_env_resolve`.
This function implements evaluation loop (also known as trampoline), which
iteratively evaluates sequence of expressions. Evaluation of single expression
can result in direct data value (which is registered with
`lsp_env_set_result_value` function) or can be delegated to execution
of another expression (which is registered with `lsp_env_set_result_eval`
function). Evaluation loop (trampoline) repeats expression evaluation
until resulting data value is fully resolved.


Source code
-----------

env.h
'''''

.. literalinclude:: ../src_c/env.h
    :language: c


env.c
'''''

.. literalinclude:: ../src_c/env.c
    :language: c
