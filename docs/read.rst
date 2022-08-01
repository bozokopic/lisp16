Data reader
===========

Data reader is responsible for reading from input stream and creating
data instances represented with input character sequences. In case of
Lisp, interpreter instructions are represented with data structures. Therefor,
parser for string representation of data is also parser form programming
language itself. Some of data types don't have string representation
(`builtin function`, `builtin syntax`, `function` and `syntax`) and
can not be produced by reader.

Character ``;`` represents beginning of comment which spawns to the end of line
(until ``\n`` character is read). White space characters (`` ``, ``\n``,
``\r``, ``\t``) and comments are ignored by reader. Only significance of
white space characters is as a data delimiter.


Number
------

Numbers as encoded as sequence of decimal characters (``0`` to ``9``).
Start of number is detected by starting decimal character.

Example of valid number representations::

    0
    1
    42


String
------

String is represented with arbitrary number of characters enclosed between
``"`` (maximum string length is 2047). ``\`` is used as escape character
in representation of:

    ``\n``, ``\r``, ``\t``, ``\\``, ``\"``

Start of string is detected by ``"`` character.

Example of valid string representations::

    ""
    "abc"
    "\""


Symbol
------

Symbol is represented with arbitrary sequence of characters. Sequence can not
include white space characters, ``(`` or ``)``. Sequence can not start with
decimal number character, ``"``, ``'``, ````` or ``,``.

Example of valid symbol representations::

    abc
    -
    +=/@
    symbol-123


Pair/list
---------

Pair is represented with form::

    (<first> . <second>)

where ``<first>`` and ``<second>`` are arbitrary data representations
(including other pars/lists).

Nested pairs of form::

    (<el_1> . (<el_2> . (.... . <el_n>)))

where ``<el_1>``, ``<el_2>``, ..., ``<el_n>`` is arbitrary data, can be
written as::

    (<el_1> <el_2> ... . <el_n>)

Special case of pair is empty list represented as::

    ()

which can be recursively specified as::

    (() . ())

Sequence of nested pairs with empty list as last element is called list::

    (<el_1> . (<el_2> . (.... . (<el_n> . ()))))

and can be written as::

    (<el_1> <el_2> ... <el_n>)

Example of valid pairs/lists representations::

    ()
    (1 . 2)
    (a . (1 . "b"))
    (1 2 3 4)
    ("abc" abc . 123)


Reader macros
-------------

To enable more concise representation of complex forms, reader recognize
few builtin reader macros. These do not introduce new data types and are used
only as more convenient representation of other standard data forms:

    * quote

        Recognized by starting character ``'``. Forms::

            '<data>

        are equivalent to::

            (quote <data>)

    * quasiquote

        Recognized by starting character `````. Forms::

            `<data>

        are equivalent to::

            (quasiquote <data>)

    * unquote

        Recognized by starting character ``,``. Forms::

            ,<data>

        are equivalent to::

            (unquote <data>)


Source code
-----------

read.h
''''''

.. literalinclude:: ../src_c/read.h
    :language: c


read.c
''''''

.. literalinclude:: ../src_c/read.c
    :language: c
