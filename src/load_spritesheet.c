#include "load_spritesheet.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Spritesheet* load_spritesheet(const char* filename, SDL_Renderer* renderer,
                              int sprite_width, int sprite_height) {
  // Load the image into an SDL_Surface
  SDL_Surface* tempSurface = IMG_Load(filename);
  if (tempSurface == NULL) {
    fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", filename,
            SDL_GetError());
    return NULL;
  }

  // Create texture from surface pixels
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  if (texture == NULL) {
    fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n",
            filename, SDL_GetError());
    SDL_FreeSurface(tempSurface);
    return NULL;
  }

  // Get the dimensions of the entire spritesheet
  int width = tempSurface->w;
  int height = tempSurface->h;

  // Free the temporary surface
  SDL_FreeSurface(tempSurface);

  // Calculate number of sprites
  int num_sprites = (width / sprite_width) * (height / sprite_height);

  // Allocate memory for the spritesheet struct
  Spritesheet* sheet = (Spritesheet*)malloc(sizeof(Spritesheet));
  if (sheet == NULL) {
    fprintf(stderr, "Unable to allocate memory for spritesheet\n");
    SDL_DestroyTexture(texture);
    return NULL;
  }

  // Set the values
  sheet->texture = texture;
  sheet->sprite_width = sprite_width;
  sheet->sprite_height = sprite_height;
  sheet->num_sprites = num_sprites;

  return sheet;
}

void free_spritesheet(Spritesheet* sheet) {
  if (sheet != NULL) {
    if (sheet->texture != NULL) {
      SDL_DestroyTexture(sheet->texture);
    }
    free(sheet);
  }
}
