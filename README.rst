lisp16
======

Simple cross platform 16bit Lisp interpreter.

* documentation - `<https://lisp16.kopic.xyz>`_
* git repository - `<https://github.com/bozokopic/lisp16.git>`_


About
-----

This project is intended as case study of Lisp implementation with following
features:

    * cross platform compatibility
        * support for 8bit/16bit architectures (microcontrollers)
        * possibility of running on POSIX systems
        * small platform compatibility layer
    * reduced Lisp dialect mostly based on Scheme
        * LISP-1 namespace
        * tail call optimization
        * macros
    * tree walking interpreter
        * possibility of multiple independent interpreter instances as part of
          single process
        * simple mark and sweep garbage collection
        * API design taking into account possibility of usage with foreign
          function interface
    * intended for educational/testing purposes
        * emphasis on source code functionality organization over binary size
          or lines of code (or other kinds of optimization)
        * accompanied documentation with implementation explanation

Following features are considered out of scope for this project:

    * real-life production usage
    * execution speed optimization
    * virtual machine or machine code compilation
    * rich standard library


Building and usage
------------------

8bit AVR microcontrollers
'''''''''''''''''''''''''

Build targeting 8bit AVR microcontrollers (tested with ATmega328P) depends
on `avr-gcc` and associated `binutils`.

Shell script::

    $ ./build-avr8.sh

produces ``build/avr8/lisp16.bin`` binary that can be written to
microcontroller's flash.

After writing binary to flash, microcontroller will execute `lisp16` repl with
UART used as input/output port.


POSIX system
''''''''''''

Build targeting POSIX systems depends on C compiler (gcc with musl C library is
used by default) and implementation of `getchar`/`putchar` and `malloc`/`free`
functions (`malloc` can be replaced with static allocation in case multiple
interpreter instances are not needed).

Shell script::

    $ ./build-posix.sh

produces ``build/posix/lisp16`` static binary.

Execution of ``build/posix/lisp16`` starts `lisp16` repl `stdin`/`stdout` used
as input/output port.


Documentation
'''''''''''''

Building of documentation depends on python with sphinx and furo modules
available.

Shell script::

    $ ./build-docs.sh

produces ``build/docs`` folder containing documentation.


License
-------

lisp16 - simple cross platform 16bit Lisp interpreter

Copyright (C) 2022 Bozo Kopic

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
