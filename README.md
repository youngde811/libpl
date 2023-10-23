
# Welcome to the LIBPL Project #

Libpl is thin C veneer over the libc _getcontext()_ function, intended for use with Swift on Linux (and specifically the
port of _opentelemetry-swift_ from Apple to Linux). The necessity for this library arises from two conditions:

- The need to emulate, as much as possible, some aspects of the Apple _os.activity_ library. I'll leave its description
to the reader's own devices; however, _opentelemetry-swift_ requires the ability to assign unique identifiers to tasks
when they create spans, all without having to carry around these identifiers to different parts of both the library and
client code.
- The restriction Swift places on using _getcontext()_ directly. The language it believes that the aforementioned
function always "returns twice". While this may be true in certain cases (think _setjmp()/longjmp()_), it is not
**always** true; it's in these latter cases, where the engineer knows precisely why he requires _getcontext()_, that
Swift believes it knows best. It doesn't.

## Author ##

[David E. Young](bosshog@passivelogic.com)
