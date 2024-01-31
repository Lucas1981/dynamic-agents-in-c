#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL_render.h"  // for SDL_Renderer

int init_graphics(int width, int height);
void cleanup_graphics(void);
void render_graphics(void);

SDL_Renderer* get_renderer(void);

#endif  // GRAPHICS_H
