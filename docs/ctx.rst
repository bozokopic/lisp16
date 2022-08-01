Context
=======

Context (also known as environment in some of Lisp implementations)
is association between symbols and their data values that apply to
specific evaluation scope. This implementation provides single
lexical context for evaluation of all names regarding of associated data
type (also known as Lisp-1 namespaces).

Basic method of introducing new scope is function definition and application.
During function definition, new function is associated with scope in which
function itself is defined. Exact copy of current context as is in moment
of definition is used as functions parent scope. During function application
new context is created which inherit all associations that were available
in parent scope.

Initial context, which is used as starting context, is initialized with
associations to builtin functions and syntaxes.

Each context contains arbitrary number of mutable entries. Single entry
defines association where any kind of data is referenced by symbol.
Together with functions that add new entries (`lsp_ctx_add`) or obtain
data associated with provided symbol (`lsp_ctx_get`), context enables
modification of data referenced by provided symbol (`lsp_ctx_set`).
During entry modification, previous data instance itself is not changed, only
entry reference is modified to point to newly provided data instance.
If child context modifies existing entry in parent context, this modifications
will also be visible in parent context.

Because of support for
`tail call optimization <https://en.wikipedia.org/wiki/Tail_call>`_,
implementation of context hierarchy relies on `lsp_ctx_copy` operation instead
of referencing parent context from child context. This method induces
additional overhead in context operation. Never the less, additional memory
allocation overhead is mostly neutralized by usage of immutable linked list
as basis for entry storage.


Source code
-----------

ctx.h
'''''

.. literalinclude:: ../src_c/ctx.h
    :language: c


ctx.c
'''''

.. literalinclude:: ../src_c/ctx.c
    :language: c
