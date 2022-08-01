Examples
========

Examples are run using interpreter build for POSIX platform. Before
executing examples, interpreter is bootstrapped with `base-large.lsp`
extensions.


Factorial
---------

Simple implementation of factorials calculation.

.. literalinclude:: ../examples/factorial.lsp
    :language: scheme

Example execution::

    $ cat src_lsp/base-large.lsp examples/factorial.lsp | build/posix/lisp16
    3628800
