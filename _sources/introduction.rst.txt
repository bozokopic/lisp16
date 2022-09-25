Introduction
============

Modern `microcontrollers <https://en.wikipedia.org/wiki/Microcontroller>`_
provide powerful computational platforms in form of
affordable and widely usable integrated circuit packages. Although, execution
performance is often more than enough for execution of complex algorithms,
some of constraints can represent challenge in implementing certain kind of
applications. In case of interpreters for high level languages, amount of
available RAM is significant factor which should be taken into account during
design of interpreter and interpreted applications. This project explores
these and similar impacts by implementing Lisp interpreter capable of
interactive execution on 8bit/32bit microcontrollers.

`Lisp <https://en.wikipedia.org/wiki/Lisp_(programming_language)>`_ is family
of high level programming languages/dialects characterized with
concise `homoiconic <https://en.wikipedia.org/wiki/Homoiconicity>`_ syntax.
`Scheme <https://en.wikipedia.org/wiki/Scheme_(programming_language)>`_, as one
of Lisp dialects, provides few powerful core functionalities which can be used
to extend language itself with wide variety of derived constructs applicable to
different programming paradigms and domains. Therefor, reduced core of Scheme,
with only few data types and builtin functions/syntaxes, can provide good base
system for execution of high level applications on embedded/constrain
platforms.

One of characteristics of most Lisp implementations is support for interactive
programming based on
`REPL <https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop>`_.
If we take into account that microcontrollers usually provide wide range of
different I/O peripherals, REPL executing instructions on microcontroller can
represent exploratory environment for testing interaction with low level
peripheries not usually available on more powerful general purpose computing
platforms. Although, this kind of environment can be provided by splitting
functionality between microcontroller and more powerful general purpose
computer which communicates with microcontroller, that approach relies on
availability of general purpose computer. By executing interpreter as a whole
on microcontroller, more self sufficient interactive platform is available in
form of a single microcontroller. Interaction with interpreter running on
microcontroller can be based on full duplex
`UART <https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter>`_
communication. In this way, wide range of simple terminals can be used (even
those utilizing other microcontrollers).

Because implementation of Lisp interpreter in C programming language doesn't
require a lot of dependencies specific to single target platform,
implementation can be based on thin abstraction layer that will provide
necessary interaction with host platform. This enables running implementation
based on same source code on different platforms, including more powerful
general purpose computers. Implementation targeting POSIX systems enables
easier testing and provides more developer friendly environment for exploring
interpreter characteristics. Usability of single code base for different
execution environments impacts some of API design decisions. Most notably,
interpreter uses memory locations referenced by additional pointer indirection
instead of statically allocated locations. This approach induces some penalties
in form of execution speed but at the same time provides API more suitable
for interaction with
`foreign function interface <https://en.wikipedia.org/wiki/Foreign_function_interface>`_
and usage of multiple independent interpreter instances as part of single POSIX
process.

Existence of this project is mostly motivated with educational and research
reasons. Therefore, significant emphasis is given on this documentation as
integrated part of project. Rest of documentation tries to explain and document
implementation in gradual bottom-up approach. It is advised to read this
documentation sequential in order because each chapter depends on explanations
available in previous chapters. Source code is organized to closely follow
documentation structure and its listing is available as part of each associated
chapter. Reader's knowledge of C programming language and related
platform/memory model is assumed.
