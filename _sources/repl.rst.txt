REPL
====

REPL, as it's name suggest, is function implementing endless loop with
following actions:

    * read

        First step is reading data from input stream.

    * evaluate

        Data that was read from input stream represent expression that
        should be evaluated by interpreter.

    * print

        Once evaluation finishes, result of evaluation is written to
        output stream. In case resulting data is ``()``, print step is
        skipped.

This loop is stopped only in case closing of input or output stream is
detected.


Source code
-----------

repl.h
''''''

.. literalinclude:: ../src_c/repl.h
    :language: c


repl.c
''''''

.. literalinclude:: ../src_c/repl.c
    :language: c
