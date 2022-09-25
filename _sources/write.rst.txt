Data writer
===========

Data writer enables serialization of data as string characters written
to output stream. Same encoding rules that apply to data reader also apply to
data writer.

Additionally, data writer will provide informative representation of data
types which can not be parsed by data reader (`builtin function`,
`builtin syntax`, `function` and `syntax`).


Source code
-----------

write.h
'''''''

.. literalinclude:: ../src_c/write.h
    :language: c


write.c
'''''''

.. literalinclude:: ../src_c/write.c
    :language: c
