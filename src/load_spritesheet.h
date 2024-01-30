#ifndef LOAD_SPRITESHEET_H
#define LOAD_SPRITESHEET_H

#include <SDL.h>

// Spritesheet structure
typedef struct Spritesheet {
    SDL_Texture* texture; // Texture for the spritesheet
    int sprite_width;
    int sprite_height;
    int num_sprites;
} Spritesheet;

// Function to load a spritesheet
Spritesheet* load_spritesheet(const char* filename, SDL_Renderer* renderer, int sprite_width, int sprite_height);

// Function to free a spritesheet
void free_spritesheet(Spritesheet* sheet);

#endif // LOAD_SPRITESHEET_H
