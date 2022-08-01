Builtin syntaxes
================

This implementation includes minimal number of builtin syntaxes. All other
constructs should be defined as user defined syntaxes in Lisp itself.

In following examples, lines starting with ``>`` represent characters
provided to input stream. Lines without starting ``>`` character represent
evaluation results written to output stream.

Available builtin syntaxes are:

    * `lambda`

        Definition of new user defined function.

        Examples::

            > ((lambda x x) 1 2 3)
            (1 2 3)

            > ((lambda (x) x) 1)
            1

            > ((lambda (x . y) y) 1 2 3)
            (2 3)

    * `syntax`

        Definition of new user defined syntax.

        Examples::

            > ((syntax x x) (lambda x x) 1 2 3)
            (1 2 3)

    * `define`

        Add new symbol binding to current context.

        Examples::

            > (define xyz 42)
            > xyz
            42

    * `set!`

        Change previously defined context entry.

        Examples::

            > (define xyz 42)
            > xyz
            42
            > (set! xyz 24)
            > xyz
            24

    * `begin`

        Evaluate multiple expressions and return result of last expression
        evaluation.

        Examples::

            > (begin 1 2 3)
            3

    * `quote`

        Evaluates to provided argument.

        Examples::

            > (quote (1 2 3))
            (1 2 3)

            > '(3 2 1)
            (3 2 1)

    * `if`

        If first argument evaluates to `thruthy` value, `if` syntax returns
        result of second argument evaluation. If first argument evaluates to
        `falsy` value, result of third argument evaluation is returned or
        ``()`` if third argument is not available.

        `Falsy` values are ``0``, ``()``, ``""`` and empty symbol.

        `Thruthy` values are all that are not `falsy`.

        Examples::

            > (if 0 1 2)
            2

            > (if "0" 1 2)
            1


Source code
-----------

syntax.h
''''''''

.. literalinclude:: ../src_c/syntax.h
    :language: c


syntax.c
''''''''

.. literalinclude:: ../src_c/syntax.c
    :language: c
