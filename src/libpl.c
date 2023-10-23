
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

#include <stdio.h>
#include <stdlib.h>

#include "libpl.h"

#if __ARM_ARCH

int
getframep(unsigned long *current, unsigned long *parent) {
  void *fp = __builtin_extract_return_addr(__builtin_frame_address(0));
  void *pfp = __builtin_extract_return_addr(__builtin_frame_address(1));

  *current = (unsigned long) fp;
  *parent = (unsigned long) pfp;
  
  return 0;
}

#else

/* We need at least an implementation for AMD64, I think. */

#include <sys/utsname.h>

int
getframep(unsigned long *identifier) {
  struct utsname uts;

  if (uname(&uts) != -1) {
    printf("libpl: not implemented for %s\n", uts.machine);
  } else {
    printf("libpl: not implemented for unrecognized architecture\n");
  }
  
  abort();

  return 0  /* NOTREACHED */
}

#endif /* __ARM_ARCH */
