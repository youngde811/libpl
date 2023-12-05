
/*
 * This is a small driver to ensure our library functions as expected. I need to add thread
 * support to more fully exercise our stuff.
 */

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include <plogic/libpl.h>

char *progname = NULL;

#define get_context_ids(tbuf, pbuf)                                     \
  do {                                                                  \
    if (pl_get_context((tbuf), (pbuf)) != -1) {                            \
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

  return rval;
}

int
main(int argc, char *argv[]) {
  progname = basename(argv[0]);

  unsigned long this;
  unsigned long parent;
  unsigned long tid;

  printf("%s: main() prints its frame addresses; then calls frodo(), which calls bilbo().\n", progname);

  get_context_ids(&this, &parent);

  frodo();

  pl_get_thread_id(&tid);

  printf("%s: main(): thread id: %ld\n", progname, tid);

  exit(0);
}
