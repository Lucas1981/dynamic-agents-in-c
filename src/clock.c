#include "clock.h"

static Uint32 now = 0;
static Uint32 then = 0;
static int first_time_set = 1;

Uint32 get_now(void) { return now; }

Uint32 get_prev(void) { return then; }

Uint32 get_elapsed_time(void) { return now - then; }

void set_time(void) {
  if (first_time_set) {
    now = SDL_GetTicks();
    then = now;
    first_time_set = 0;
  } else {
    then = now;
    now = SDL_GetTicks();
  }
}
