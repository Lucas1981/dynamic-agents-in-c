#include "input.h"

#include <SDL.h>

static KeyState keyState = {0, 0, 0, 0};

KeyState *get_key_state() { return &keyState; }

void handle_input(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        keyState.left = 1;
        break;
      case SDLK_RIGHT:
        keyState.right = 1;
        break;
      case SDLK_SPACE:
        keyState.space = 1;
        break;
      case SDLK_RETURN:
        keyState.enter = 1;
        break;
    }
  } else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        keyState.left = 0;
        break;
      case SDLK_RIGHT:
        keyState.right = 0;
        break;
      case SDLK_SPACE:
        keyState.space = 0;
        break;
      case SDLK_RETURN:
        keyState.enter = 0;
        break;
    }
  }
}
