
/*
 * Standard header file for libpl.
 */

#ifndef _LIBPL_H
#define _LIBPL_H 1

int get_context(unsigned long *current, unsigned long *parent);
int get_context_frame_addr(unsigned long *current, unsigned long *parent);

void use_return_address();
void use_frame_address();

#endif  /* _LIBPL_H */
