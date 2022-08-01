Evaluation
==========

Because Lisp code is represented with data structures, each data structure
can be used as interpreter instruction. Evaluation of data, when used as
interpreter expression, is defined according to data type:

    * number, string, builtin function, builtin syntax, function, syntax

        Data of this type evaluate to itself (expression consisting of
        single instance of data evaluates to provided data instance).

    * symbol

        Symbols evaluate to data associated to provided symbol in
        current evaluation context. If context entry associated with the symbol
        is not available, evaluation error is signaled.

    * pair/list

        Lists evaluate to function/syntax application. As first step,
        first element of list is evaluated. If first element evaluates
        to function or builtin function, all remaining elements are also
        evaluated and used as provided arguments. If first element evaluates
        to syntax or builtin syntax, remaining list elements are not evaluated
        and are used as provided arguments. After evaluation of first element
        and possible argument evaluation (in case of functions), evaluation
        is delegated to function/syntax application (described in following
        chapters). If first list element doesn't evaluate to function/syntax,
        evaluation error is signaled. Exception to this rule is empty
        list which evaluates to itself.


Source code
-----------

eval.h
''''''

.. literalinclude:: ../src_c/eval.h
    :language: c


eval.c
''''''

.. literalinclude:: ../src_c/eval.c
    :language: c
