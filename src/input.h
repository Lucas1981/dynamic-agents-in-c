#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

// Structure to hold key states
typedef struct {
  int left;
  int right;
  int space;
  int enter;
} KeyState;

KeyState *get_key_state();
void handle_input(SDL_Event event);

#endif
