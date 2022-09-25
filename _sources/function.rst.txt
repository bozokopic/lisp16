Builtin functions
=================

In following examples, lines starting with ``>`` represent characters
provided to input stream. Lines without starting ``>`` character represent
evaluation results written to output stream.

Available builtin functions:

    * `eval`

    * `apply`

    * `error`

    * `cons`

    * `set-car!`

    * `set-cdr!`

    * `number?`

    * `pair?`

    * `string?`

    * `symbol?`

    * `function?`

    * `syntax?`

    * `eq?`

    * `equal?`

    * `>`

    * `<`

    * `+`

    * `-`

    * `*`

    * `/`

    * `read`

    * `read-u8`

    * `peek-u8`

    * `write`

    * `write-u8`

    * `make-string`

    * `string-length`

    * `string-ref`

    * `string-set!`


Source code
-----------

function.h
''''''''''

.. literalinclude:: ../src_c/function.h
    :language: c


function.c
''''''''''

.. literalinclude:: ../src_c/function.c
    :language: c
