#include "frames.h"

#include <stdio.h>  // for NULL

#include "SDL_rect.h"          // for SDL_Rect
#include "SDL_render.h"        // for SDL_RenderCopy, SDL_Renderer
#include "graphics.h"          // for get_renderer
#include "load_spritesheet.h"  // for free_spritesheet, load_spritesheet

#define MAX_FRAMES 16
#define FRAMES_PER_ROW 4

// Assuming a global array of frames is defined somewhere
static Frame global_frames[MAX_FRAMES];  // MAX_FRAMES is a defined constant

// Function to provide access to the global frames
static Spritesheet* sheet;
static SDL_Renderer* renderer;

Frame* get_frames(void) { return global_frames; }

void init_frames(void) {
  renderer = get_renderer();
  sheet = load_spritesheet("./assets/images/spritesheet.png", renderer, 64, 64);
  renderer = get_renderer();
  int num_frames = sheet->num_sprites;

  for (int i = 0; i < num_frames; ++i) {
    global_frames[i].x = (i % FRAMES_PER_ROW) * FRAME_WIDTH;
    global_frames[i].y = (i / FRAMES_PER_ROW) * FRAME_HEIGHT;
  }
}

void draw_frame(int x, int y, Frame* frame) {
  if (renderer == NULL || sheet == NULL || frame == NULL) {
    return;
  }

  SDL_Rect src_rect = {frame->x, frame->y, FRAME_WIDTH, FRAME_HEIGHT};
  SDL_Rect dest_rect = {x, y, FRAME_WIDTH,
                        FRAME_HEIGHT};  // Modify as needed for position

  SDL_RenderCopy(renderer, sheet->texture, &src_rect, &dest_rect);
}

void cleanup_frames(void) { free_spritesheet(sheet); }
