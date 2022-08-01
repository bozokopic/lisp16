Data types
==========

All data types are encoded as one or more consecutive 16bit words (cells).
Most significant bit of each 16bit word is reserved for memory manager usage
and remaining 15bits are used for identifying data types and encoding
data values. Most significant data bits of first word identifies
data type. Most significant bit is referenced as bit 15 and least significant
bit as bit 0.

Implementation mostly uses static inline functions defined in header file,
instead of preprocessor definitions, to provide API more suitable for
foreign function interface.


Number
------

Data type representing signed integer values of arbitrary length. Although
encoding itself doesn't limit value size, to provide easier interface for
data manipulation, values are limited to signed integers represented with
32bit dual complement encoding. Single number is encoded with one or more
words:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 0 1 s v v v v v v v v v v v v |
    +---------+---------------------------------+
    | n + 1   | m 1 v v v v v v v v v v v v v v |
    +---------+---------------------------------+
    | ...     | ...                             |
    +---------+---------------------------------+
    | n + i   | m 1 v v v v v v v v v v v v v v |
    +---------+---------------------------------+
    | ...     | ...                             |
    +---------+---------------------------------+
    | n + m   | m 0 v v v v v v v v v v v v v v |
    +---------+---------------------------------+

where:

    * Bit 15 of each word (`m`) is reserved for memory management.

    * Bit 14 of first word (``0``) identifies number type.

    * Bit 13 of first word and bit 14 of other words represents "more follows".
      Only in last word (`n + m`) is this bit set to ``0``.

    * Bit 12 of first word (`s`) identifies sign.

    * Rest of bits are used as dual complement encoded integer value where
      word `n` contains most significant bits and word `n + m` contains
      least significant bits.


Pair
----

Data type representing two addresses referencing word locations (usually
known as cons cell). Address values are limited to 14bit unsigned integers
which enables encoding of this type with two words:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 0 a a a a a a a a a a a a a |
    +---------+---------------------------------+
    | n + 1   | m a b b b b b b b b b b b b b b |
    +---------+---------------------------------+

where:

    * Bit 15 of each word (`m`) is reserved for memory management.

    * Bits 14 and 13 of first word (``10``) identify pair type.

    * 14 `a` bits encode first address value.

    * 14 `b` bits encode second address value.


String
------

Data type representing zero of more 8bit values. Single string is represented
with one or more words:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 1 0 0 s s s s s s s s s s s |
    +---------+---------------------------------+
    | n + 1   | m a a a a a a a a b b b b b b b |
    +---------+---------------------------------+
    | n + 2   | m b c c c c c c c c d d d d d d |
    +---------+---------------------------------+
    | ...     | ...                             |
    +---------+---------------------------------+

where:

    * Bit 15 of each word (`m`) is reserved for memory management.

    * Bits 14, 13, 12 and 11 of first word (``1100``) identify string type.

    * 11 `s` bits represent string length (maximum string length is 2047).

    * Bits `a`, `b`, `c`, ... represent 8bit values.

This encoding schema tries to optimize memory usage but at the same time
introduces significant overhead in manipulating string data.


Symbol
------

Symbols are used as human readable labels associated with data values. They
are encoded as 8bit characters similarly as string data:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 1 0 1 s s s s s s s s s s s |
    +---------+---------------------------------+
    | n + 1   | m a a a a a a a a b b b b b b b |
    +---------+---------------------------------+
    | n + 2   | m b c c c c c c c c d d d d d d |
    +---------+---------------------------------+
    | ...     | ...                             |
    +---------+---------------------------------+

where:

    * Bit 15 of each word (`m`) is reserved for memory management.

    * Bits 14, 13, 12 and 11 of first word (``1101``) identify symbol type.

    * 11 `s` bits represent symbol length (maximum symbol length is 2047).

    * Bits `a`, `b`, `c`, ... represent 8bit character values.


Builtin function
----------------

Builtin functions are referenced by function's index and encoded with
single word:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 1 1 0 0 i i i i i i i i i i |
    +---------+---------------------------------+

where:

    * Bit 15 (`m`) is reserved for memory management.

    * Bits 14, 13, 12, 11 and 10 (``11100``) identify builtin function type.

    * 10 `i` bits represent builtin function index.


Builtin syntax
--------------

Builtin syntaxes are referenced by syntax's index and encoded with
single word:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 1 1 0 1 i i i i i i i i i i |
    +---------+---------------------------------+

where:

    * Bit 15 (`m`) is reserved for memory management.

    * Bits 14, 13, 12, 11 and 10 (``11101``) identify builtin syntax type.

    * 10 `i` bits represent builtin syntax index.


Function
--------

Functions are defined by parent context, list of argument names and function
body. Type identifier together with 14bit addressees of associated values are
encoded within 4 words:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 1 1 1 0 x x x x x x x x x x |
    +---------+---------------------------------+
    | n + 1   | m x c c c c c c c c c c c c c c |
    +---------+---------------------------------+
    | n + 2   | m x a a a a a a a a a a a a a a |
    +---------+---------------------------------+
    | n + 3   | m x b b b b b b b b b b b b b b |
    +---------+---------------------------------+

where:

    * Bit 15 of each word (`m`) is reserved for memory management.

    * Bits 14, 13, 12, 11 and 10 of first word (``11110``) identify function
      type.

    * 14 `c` bits represent parent context address.

    * 14 `a` bits represent argument name list address.

    * 14 `b` bits represent body definition address.

    * `x` bits are not used.


Syntax
------

Syntaxes are defined by parent context, list of argument names and syntax
body. Type identifier together with 14bit addressees of associated values are
encoded within 4 words:

    +---------+---------------------------------+
    | address | data                            |
    +=========+=================================+
    | n       | m 1 1 1 1 0 x x x x x x x x x x |
    +---------+---------------------------------+
    | n + 1   | m x c c c c c c c c c c c c c c |
    +---------+---------------------------------+
    | n + 2   | m x a a a a a a a a a a a a a a |
    +---------+---------------------------------+
    | n + 3   | m x b b b b b b b b b b b b b b |
    +---------+---------------------------------+

where:

    * Bit 15 of each word (`m`) is reserved for memory management.

    * Bits 14, 13, 12, 11 and 10 of first word (``11110``) identify syntax
      type.

    * 14 `c` bits represent parent context address.

    * 14 `a` bits represent argument name list address.

    * 14 `b` bits represent body definition address.

    * `x` bits are not used.


Source code
-----------

cell.h
''''''

.. literalinclude:: ../src_c/cell.h
    :language: c


cell.c
''''''

.. literalinclude:: ../src_c/cell.c
    :language: c
