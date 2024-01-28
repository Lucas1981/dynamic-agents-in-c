#include "clock.h"

static Uint32 now = 0;
static Uint32 then = 0;
static int first_time_set = 1;

Uint32 get_now() { return now; }

Uint32 get_prev() { return then; }

Uint32 get_elapsed_time() { return now - then; }

void set_time() {
  if (first_time_set) {
    now = SDL_GetTicks();
    then = now;
    first_time_set = 0;
  } else {
    then = now;
    now = SDL_GetTicks();
  }
}
