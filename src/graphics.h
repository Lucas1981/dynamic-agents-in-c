#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

// Initializes the graphics system, including creating the window
int init_graphics(int width, int height);

// Cleans up the graphics system
void cleanup_graphics();

// Draws a red rectangle
void draw_red_rectangle(int x, int y, int width, int height);

// Renders the current frame
void render_graphics();

SDL_Renderer* get_renderer();

#endif  // GRAPHICS_H
