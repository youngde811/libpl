
/*
 * This is a small driver to ensure our library functions as expected.
 */

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include <plogic/libpl.h>

char *progname = NULL;

static int
frodo() {
  int rval = 0;
  unsigned long identifier;

  if ((rval = activity_create(&identifier)) != -1) {
    printf("%s: frodo(): identifier: %lu", progname, identifier);
  } else {
    printf("%s: frodo(): failed to retrieve identifier!", progname);
  }

  return rval;
}

int
main(int argc, char *argv[]) {
  int rval = 0;
  unsigned long identifier;

  progname = basename(argv[0]);
  
  if ((rval = activity_create(&identifier)) != -1) {
    printf("%s: main(): identifier is %lu\n", progname, identifier);

    frodo();
  } else {
    printf("%s: main(): failed to retrieve identifier!", progname);
  }

  exit(0);
}
