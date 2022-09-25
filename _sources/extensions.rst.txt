Extensions
==========

Base Lisp language, provided by interpreter with builtin functions/syntaxes,
is deliberately designed with limited set of functionality.

To provide more usable development environment, additional extensions
written in Lisp are available. These extensions are implemented as set of
instructions that should be evaluated by interpreter immediately after
startup. After this bootstrapping evaluation finished, additional
functionalities are available as part of active context.


Source code
-----------

base-small.lsp
''''''''''''''

.. literalinclude:: ../src_lsp/base-small.lsp
    :language: scheme


base-large.lsp
''''''''''''''

.. literalinclude:: ../src_lsp/base-large.lsp
    :language: scheme
