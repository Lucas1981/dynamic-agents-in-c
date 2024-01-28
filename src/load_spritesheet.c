#include "load_spritesheet.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Spritesheet* loadSpritesheet(const char* filename, SDL_Renderer* renderer,
                             int spriteWidth, int spriteHeight) {
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
  int numSprites = (width / spriteWidth) * (height / spriteHeight);

  // Allocate memory for the spritesheet struct
  Spritesheet* sheet = (Spritesheet*)malloc(sizeof(Spritesheet));
  if (sheet == NULL) {
    fprintf(stderr, "Unable to allocate memory for spritesheet\n");
    SDL_DestroyTexture(texture);
    return NULL;
  }

  // Set the values
  sheet->texture = texture;
  sheet->spriteWidth = spriteWidth;
  sheet->spriteHeight = spriteHeight;
  sheet->numSprites = numSprites;

  return sheet;
}

void freeSpritesheet(Spritesheet* sheet) {
  if (sheet != NULL) {
    if (sheet->texture != NULL) {
      SDL_DestroyTexture(sheet->texture);
    }
    free(sheet);
  }
}
