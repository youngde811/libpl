
/*
 * This is a small driver to ensure our library functions as expected.
 */

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include <plogic/libpl.h>

char *progname = NULL;

#define get_identifier(buf) activity_create((buf))

static int
bilbo() {
  unsigned long identifier;
  int rval = get_identifier(&identifier);
  
  if (rval != -1) {
    printf("%s: bilbo(): identifier: %lu\n", progname, identifier);
  } else {
    printf("%s: bilbo(): failed to retrieve identifier!\n", progname);
  }

  return rval;
}

static int
frodo() {
  unsigned long identifier;
  int rval = get_identifier(&identifier);
  
  if (rval != -1) {
    printf("%s: frodo(): identifier: %lu\n", progname, identifier);
  } else {
    printf("%s: frodo(): failed to retrieve first identifier!\n", progname);
  }

  rval = bilbo();
  
  if ((rval = get_identifier(&identifier)) != -1) {
    printf("%s: frodo(): this identifier should be the same as the first for frodo above: %lu\n", progname, identifier);
  } else {
    printf("%s: frodo(): failed to retrieve second identifier!\n", progname);
  }
  
  return rval;
}

int
main(int argc, char *argv[]) {
  int rval = 0;
  unsigned long identifier;

  progname = basename(argv[0]);
  
  if ((rval = get_identifier(&identifier)) != -1) {
    printf("%s: main(): identifier is %lu\n", progname, identifier);

    frodo();
  } else {
    printf("%s: main(): failed to retrieve identifier!\n", progname);
  }

  exit(0);
}
