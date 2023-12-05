
/*
 * Standard header file for libpl.
 */

#ifndef _LIBPL_H
#define _LIBPL_H 1

typedef enum {
  RETURN_ADDR,
  FRAME_ADDR
} context_type_t;

/*
 * These two variants of get_context() are subtly different. The first variant returns
 * the address of the calling function's frame (and its parent frame); the second variant
 * supplies the actual return address of the calling function (and its parent). By default,
 * variant one (fetching the calling function's frame) seems to be the most reliable on
 * arm64 and x86_64.
 *
 * NB: On some machines it may be impossible to determine the return address of any function
 * other than the current one; in such cases, the parent value will be set to zero (0).
 */

int pl_get_context_frame_addr(unsigned long *current, unsigned long *parent);
int pl_get_context(unsigned long *current, unsigned long *parent);
int pl_get_thread_id(unsigned long *id);

void pl_with_context_type(context_type_t);

#endif  /* _LIBPL_H */
