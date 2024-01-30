#include "input.h"

#include <SDL.h>

static KeyState key_state = {0, 0, 0, 0, 0};
static void handle_input(SDL_Event event);
static int quit = 0;

KeyState *get_key_state() { return &key_state; }
int get_quit() { return quit; }

void handle_inputs() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    handle_input(event);
  }
}

static void handle_input(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        key_state.left = 1;
        break;
      case SDLK_RIGHT:
        key_state.right = 1;
        break;
      case SDLK_SPACE:
        key_state.space = 1;
        break;
      case SDLK_RETURN:
        key_state.enter = 1;
        break;
      case SDLK_ESCAPE:
        key_state.escape = 1;
    }
  } else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        key_state.left = 0;
        break;
      case SDLK_RIGHT:
        key_state.right = 0;
        break;
      case SDLK_SPACE:
        key_state.space = 0;
        break;
      case SDLK_RETURN:
        key_state.enter = 0;
        break;
      case SDLK_ESCAPE:
        key_state.escape = 0;
    }
  } else if (event.type == SDL_QUIT) {
    quit = 1;
  }
}
