
/*
 * This library is used to create an "activity context" that attempts to mimic the Apple
 * os.activity library's os_activity_get_identifier() function. In reality, there is no
 * analog to Apple's library for Linux; rather, we're left with trying to create a stack-local
 * unique ID, which is very platform-dependent.
 *
 * NB: The technique employed by this library is not reliable. It uses the libc getcontext()
 * function to retrieve stack data, then logically ORs together the stack pointer and program counter,
 * hoping to create a unique ID for any particular stack, regardless of thread. How successful we can
 * be depends much on the definition of ucontext_t, and the information found in its mcontext_t struct.
 * On ARM64, we get some good stuff and can make a reasonable attempt. It remains to be seen what other
 * architectures, such as AMD64, give us.
 */

#include "libpl.h"

int
activity_create(unsigned long *identifier) {
  ucontext_t ucp;
  int rval = 0;
      
  if ((rval = getcontext(&ucp)) == 0) {
    *identifier = (ucp.uc_mcontext.__sp | ucp.uc_mcontext.__pc);
  }

  return rval;
}
