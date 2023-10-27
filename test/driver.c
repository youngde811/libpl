
/*
 * This is a small driver to ensure our library functions as expected.
 */

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include <plogic/libpl.h>

char *progname = NULL;

#define get_context_ids(tbuf, pbuf)                                     \
  do {                                                                  \
    if (get_context((tbuf), (pbuf)) != -1) {                            \
      printf("%s: %s: this: %lu; parent: %lu\n", progname, __FUNCTION__, (*tbuf), (*pbuf)); \
    } else {                                                            \
      printf("%s: %s: failed to retrieve stack pointer!\n", progname, __FUNCTION__); \
      exit(1);                                                          \
    }                                                                   \
  } while(0)                                                            \

static int
bilbo() {
  int rval = 0;
  unsigned long this;
  unsigned long parent;

  get_context_ids(&this, &parent);

  return rval;
}

static int
frodo() {
  int rval = 0;
  unsigned long this;
  unsigned long parent;

  get_context_ids(&this, &parent);

  rval = bilbo();

  get_context_ids(&this, &parent);

  printf("%s: frodo(): the above frames should be the same as the first for %s above: %lu:%lu\n", progname, __FUNCTION__, this, parent);
  
  return rval;
}

int
main(int argc, char *argv[]) {
  unsigned long identifier;

  progname = basename(argv[0]);

  frodo();

  exit(0);
}
