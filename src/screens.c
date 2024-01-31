#include "screens.h"

#include <SDL_image.h>  // for IMG_Load, IMG_GetError
#include <stdio.h>      // for NULL, fprintf, stderr

#include "SDL_error.h"    // for SDL_GetError
#include "SDL_render.h"   // for SDL_CreateTextureFromSurface, SDL_DestroyTe...
#include "SDL_surface.h"  // for SDL_FreeSurface, SDL_Surface
#include "graphics.h"     // for get_renderer

// Array to hold screen textures
static SDL_Texture* screens[NUM_SCREENS] = {NULL};

void load_screens(void) {
  SDL_Renderer* renderer = get_renderer();
  const char* screen_files[NUM_SCREENS] = {"./assets/images/title-screen.png",
                                           "./assets/images/level.png"};

  for (int i = 0; i < NUM_SCREENS; i++) {
    SDL_Surface* temp_surface = IMG_Load(screen_files[i]);
    if (!temp_surface) {
      fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n",
              screen_files[i], IMG_GetError());
      continue;
    }

    screens[i] = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    if (!screens[i]) {
      fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n",
              screen_files[i], SDL_GetError());
    }
  }
}

void draw_screen(ScreenType type) {
  if (type < 0 || type >= NUM_SCREENS) {
    return;
  }

  SDL_Renderer* renderer = get_renderer();
  SDL_Texture* screen = screens[type];
  SDL_RenderCopy(renderer, screen, NULL, NULL);
}

void cleanup_screens(void) {
  for (int i = 0; i < NUM_SCREENS; i++) {
    if (screens[i]) {
      SDL_DestroyTexture(screens[i]);
      screens[i] = NULL;
    }
  }
}
