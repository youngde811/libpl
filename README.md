
# Welcome to the LIBPL Project #

Libpl is thin C veneer over the libc _getcontext()_ function, intended for use with Swift on Linux. The necessity for
this library arises from the restriction Swift places on using _getcontext()_ directly; it believes that the
aforementioned function always "returns twice". While this may be true in certain cases, it is not **always** true; it's
these latter cases, where the engineer knows precisely why he requires _getcontext()_, that Swift believes it knows
best. Hence this project.

## Author ##

[David E. Young](bosshog@passivelogic.com)
