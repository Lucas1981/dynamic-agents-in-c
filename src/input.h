#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

// Structure to hold key states
typedef struct {
  int left;
  int right;
  int space;
  int enter;
  int escape;
} KeyState;

KeyState *get_key_state();
void handle_inputs();
int get_quit();

#endif
