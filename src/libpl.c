
/*
 * This is a needless library used to deceive Swift into allowing us to use getcontext() in
 * its basic, "returns once" form. This code is required just on Linux
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
