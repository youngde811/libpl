
/*
 * This is a small driver to ensure our library functions as expected.
 */

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include <plogic/libpl.h>

char *progname = NULL;

#define get_framep(buf)                                                 \
  do {                                                                  \
    if (getframep((buf)) != -1) {                                       \
      printf("%s: %s: identifier: %lu\n", progname, __FUNCTION__, *buf); \
    } else {                                                            \
      printf("%s: %s: failed to retrieve stack pointer!\n", progname, __FUNCTION__); \
      exit(1);                                                          \
    }                                                                   \
  } while(0)                                                            \

static int
bilbo() {
  int rval = 0;
  unsigned long identifier;

  get_framep(&identifier);

  return rval;
}

static int
frodo() {
  int rval = 0;
  unsigned long identifier;

  get_framep(&identifier);

  rval = bilbo();

  get_framep(&identifier);

  printf("%s: frodo(): the above identifier should be the same as the first for %s above: %lu\n", progname, __FUNCTION__, identifier);
  
  return rval;
}

int
main(int argc, char *argv[]) {
  unsigned long identifier;

  progname = basename(argv[0]);

  get_framep(&identifier);

  frodo();

  exit(0);
}
