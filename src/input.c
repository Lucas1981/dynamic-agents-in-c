#include "input.h"

#include "SDL_events.h"   // for SDL_Event, SDL_PollEvent, SDL_KEYDOWN, SDL_...
#include "SDL_keycode.h"  // for SDLK_ESCAPE, SDLK_LEFT, SDLK_RETURN, SDLK_R...

static KeyState key_state = {0, 0, 0, 0, 0};
static void handle_input(SDL_Event event);
static int quit = 0;

KeyState *get_key_state(void) { return &key_state; }
int get_quit(void) { return quit; }

void handle_inputs(void) {
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
        break;
      default:
        break;
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
      default:
        break;
    }
  } else if (event.type == SDL_QUIT) {
    quit = 1;
  }
}
