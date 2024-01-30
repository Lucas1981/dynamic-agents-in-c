#ifndef LOAD_SPRITESHEET_H
#define LOAD_SPRITESHEET_H

#include <SDL.h>

typedef struct Spritesheet {
  SDL_Texture* texture;  // Texture for the spritesheet
  int sprite_width;
  int sprite_height;
  int num_sprites;
} Spritesheet;

Spritesheet* load_spritesheet(const char* filename, SDL_Renderer* renderer,
                              int sprite_width, int sprite_height);
void free_spritesheet(Spritesheet* sheet);

#endif  // LOAD_SPRITESHEET_H
