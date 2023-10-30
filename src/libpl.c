
/*
 * This library is used to create an "activity context" that attempts to mimic the Apple
 * os.activity library's os_activity_get_identifier() function. In reality, there is no
 * analog to Apple's library for Linux; rather, we're left with trying to create a stack-local
 * unique ID, which is very platform-dependent.
 *
 * NB: The technique employed by this library is not portable, or even reliable on certain machines.
 * It uses gcc builtin functions to retrieve the current and parent stack frame addresses, documented
 * here: https://gcc.gnu.org/onlinedocs/gcc/Return-Address.html.
 * How successful we can be depends much on the platform architecture. On ARM64 we get good values.
 * It remains to be seen what other architectures, such as AMD64, give us.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "libpl.h"

#if __GNUC__

int
get_context(unsigned long *current, unsigned long *parent) {
  void *fp = __builtin_extract_return_addr(__builtin_return_address(0));
  void *pfp = __builtin_extract_return_addr(__builtin_return_address(1));

  *current = (unsigned long) fp;
  *parent = (unsigned long) pfp;
  
  return 0;
}

int
get_context_frame_addr(unsigned long *current, unsigned long *parent) {
  void *fp = __builtin_extract_return_addr(__builtin_frame_address(0));
  void *pfp = __builtin_extract_return_addr(__builtin_frame_address(1));

  *current = (unsigned long) fp;
  *parent = (unsigned long) pfp;
  
  return 0;
}

#else

/* Only GNU gcc is supported as a compiler, due to the system-level builtin functions we must use */

#error "libpl.c: *** Only GNU's gcc compiler is supported, due to the need for system-level builtin functions ***"

#endif /* __GNUC__ */
