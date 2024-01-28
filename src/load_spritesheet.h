#ifndef LOAD_SPRITESHEET_H
#define LOAD_SPRITESHEET_H

#include <SDL.h>

// Spritesheet structure
typedef struct Spritesheet {
    SDL_Texture* texture; // Texture for the spritesheet
    int spriteWidth;
    int spriteHeight;
    int numSprites;
} Spritesheet;

// Function to load a spritesheet
Spritesheet* loadSpritesheet(const char* filename, SDL_Renderer* renderer, int spriteWidth, int spriteHeight);

// Function to free a spritesheet
void freeSpritesheet(Spritesheet* sheet);

#endif // LOAD_SPRITESHEET_H
