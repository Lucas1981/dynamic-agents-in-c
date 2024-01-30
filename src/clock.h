#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>

Uint32 get_now(void);
Uint32 get_prev(void);
Uint32 get_elapsed_time(void);
void set_time(void);

#endif  // CLOCK_H
