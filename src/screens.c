#include "screens.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "graphics.h"

// Array to hold screen textures
static SDL_Texture* screens[NUM_SCREENS] = {NULL};

void load_screens() {
  SDL_Renderer* renderer = get_renderer();
  const char* screenFiles[NUM_SCREENS] = {"./assets/images/title-screen.png",
                                          "./assets/images/level.png"};

  for (int i = 0; i < NUM_SCREENS; i++) {
    SDL_Surface* tempSurface = IMG_Load(screenFiles[i]);
    if (!tempSurface) {
      fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n",
              screenFiles[i], IMG_GetError());
      continue;
    }

    screens[i] = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!screens[i]) {
      fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n",
              screenFiles[i], SDL_GetError());
    }
  }
}

void draw_screen(SCREEN_TYPE type) {
  if (type < 0 || type >= NUM_SCREENS) {
    return;
  }

  SDL_Renderer* renderer = get_renderer();
  SDL_Texture* screen = screens[type];
  SDL_RenderCopy(renderer, screen, NULL, NULL);
}

void cleanup_screens() {
  for (int i = 0; i < NUM_SCREENS; i++) {
    if (screens[i]) {
      SDL_DestroyTexture(screens[i]);
      screens[i] = NULL;
    }
  }
}
