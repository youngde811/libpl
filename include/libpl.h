
/*
 * Standard header file for libpl.
 */

#ifndef _LIBPL_H
#define _LIBPL_H 1

typedef enum {
  RETURN_ADDR,
  FRAME_ADDR
} context_type_t;

int get_context(unsigned long *current, unsigned long *parent);
int get_context_frame_addr(unsigned long *current, unsigned long *parent);

void with_context_type(context_type_t);

#endif  /* _LIBPL_H */
