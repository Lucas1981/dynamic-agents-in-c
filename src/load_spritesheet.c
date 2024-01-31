#include "load_spritesheet.h"

#include <SDL_image.h>  // for IMG_Load
#include <stdio.h>      // for NULL, fprintf, stderr
#include <stdlib.h>     // for free, malloc

#include "SDL_error.h"    // for SDL_GetError
#include "SDL_surface.h"  // for SDL_FreeSurface, SDL_Surface

Spritesheet* load_spritesheet(const char* filename, SDL_Renderer* renderer,
                              int sprite_width, int sprite_height) {
  // Load the image into an SDL_Surface
  SDL_Surface* temp_surface = IMG_Load(filename);
  if (temp_surface == NULL) {
    fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", filename,
            SDL_GetError());
    return NULL;
  }

  // Create texture from surface pixels
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
  if (texture == NULL) {
    fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n",
            filename, SDL_GetError());
    SDL_FreeSurface(temp_surface);
    return NULL;
  }

  // Get the dimensions of the entire spritesheet
  int width = temp_surface->w;
  int height = temp_surface->h;

  // Free the temporary surface
  SDL_FreeSurface(temp_surface);

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
