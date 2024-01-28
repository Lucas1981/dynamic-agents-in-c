#include "graphics.h"

#include <SDL.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

int init_graphics(int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow("Dynamic Agents in C", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return -1;
  }

  return 0;
}

void cleanup_graphics() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

void draw_red_rectangle(int x, int y, int width, int height) {
  SDL_Rect rect = {x, y, width, height};
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // RGBA for red
  SDL_RenderFillRect(renderer, &rect);
}

void render_graphics() {
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Clear with black
  SDL_RenderClear(renderer);
}

SDL_Renderer* get_renderer() { return renderer; }
