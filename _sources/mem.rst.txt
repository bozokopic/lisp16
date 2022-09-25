Memory management
=================

Functions declared in `mem.h` provide interface for usage of dynamically
allocated data. All other modules interact with dynamic data only through
these functions.


Memory layout
-------------

State of memory management is represented with structure `lsp_mem_t`. It
contains continuous memory block of platform specific word count.
Addresses used for referencing each data correspond to this memory block
starting word index. Because addresses are represented with 14bit unsigned
integer values, usable memory for allocation of dynamic data is limited to
16384 words (32768 bytes). In case of memory constrained systems, this
size is even smaller.


Data allocation
---------------

Each word (event those which are not single data starting words) have
single bit dedicated for memory management usage. This most significant bit
represent words current usage state where ``0`` represents used word (word is
used for representing data content) and ``1`` represent unused word (word is
available for allocation of new data instance).

During allocation of new data, all available words are searched for
continuous block of unused words which could be used to represent newly
allocated data content. If such word block could not be found, garbage
collection procedure is triggered, after which search for free block is
repeated. If search is not successful for the second time, allocation
of new data fails. If search is successful, address of newly allocated data
is remembered and used as starting address for future allocation searches.

All `lsp_mem_create_*` functions, used for data allocation, add allocated
data to list of accessible root data. Management of accessible data is
possible with `lsp_mem_inc_ref` and `lsp_mem_dec_ref` which increase and
decrease references to root data. Once data is not part of root list or is not
referenced by other data which are part of root list, it is considered
not accessible and can be reclaimed by garbage collector.

During memory initialization, often used data instances are preallocated and
available as part of `lsp_mem_t` structure (`nil`, `zero`, `one`, `quote`,
`quasiquote`, `unquote` and `unquote_splicing`).


Garbage collector
-----------------

Garbage collector is based on variant of simple mark and sweep design.
Initially, all memory words are marked as free. Once words are used for data
representation, used words are immediately marked as non free. After
repeated allocation of new data instances, pool of available free words
is depleted and garbage procedure is started.

As first step of garbage collection, all memory words are marked as free.
Then, words used for representation of root list are marked as non free by
usage of recursive function which, together with immediately used words, marks
all other referenced data words. Data types which reference other data are
`pair`, `function` and `syntax`. After all data directly and indirectly
referenced by root list is marked as used, garbage collection finishes
(all other words remain marked as unused).


Data usage
----------

Together with data allocation function, memory management functions include
interface for manipulation and usage of allocated data. These include
`lsp_mem_is_*` function for data type assertion and `lsp_mem_get_*` functions
for data content retrieval. This functions provide thin wrapper for `cell.h`
functions with mapping of data addresses to data words.

All data types, except for `string` and `pair` are considered immutable -
data content is initialized during allocation and is not mutated afterwards.
In case of `string` and `pair` data, `lsp_mem_set_*` functions enable
in place modification of data instance content. In case of `string` data,
only content of preallocated size can be modified (size of string can not
change after allocation).

All other parts of interpreter use only `lsp_mem_*` wrappers instead of
direct `lsp_cell_*` function usage.


Symbol reusability
------------------

Because symbols are immutable, memory usage optimization can be done during
symbol allocation. Each time new symbol should be allocated, content of
all memory words is searched for already allocated symbol with same content.
If such instance is found, reference to already existing symbol is returned
together with incrementing this reference in root list. This optimization
comes with cost of additional memory search during each symbol allocation.


Ownership conventions
---------------------

Since data availability is controlled with usage create function and
reference incrementation/decrementation, convention for memory ownership is
required. In case of this project, if not explicitly specified otherwise,
caller of function is owner of all input arguments and remains their owner
after function execution finished (function temporary borrows ownership
of input arguments). If function returns data, ownership of returned data
is passed to function caller. It is responsibility of function caller to
release data returned as result of function execution.


Source code
-----------

mem.h
'''''

.. literalinclude:: ../src_c/mem.h
    :language: c


mem.c
'''''

.. literalinclude:: ../src_c/mem.c
    :language: c
