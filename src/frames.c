#include "frames.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"

#define MAX_FRAMES 16
#define FRAMES_PER_ROW 4

// Assuming a global array of frames is defined somewhere
static Frame globalFrames[MAX_FRAMES];  // MAX_FRAMES is a defined constant

// Function to provide access to the global frames
Spritesheet* sheet;
SDL_Renderer* renderer;

Frame* get_frames() { return globalFrames; }

void initFrames(Spritesheet* spritesheet) {
  sheet = spritesheet;
  renderer = get_renderer();
  int numFrames = sheet->numSprites;

  for (int i = 0; i < numFrames; ++i) {
    globalFrames[i].x = (i % FRAMES_PER_ROW) * FRAME_WIDTH;
    globalFrames[i].y = (i / FRAMES_PER_ROW) * FRAME_HEIGHT;
  }
}

void drawFrame(int x, int y, Frame* frame) {
  if (renderer == NULL || sheet == NULL || frame == NULL) {
    return;
  }

  SDL_Rect srcRect = {frame->x, frame->y, FRAME_WIDTH, FRAME_HEIGHT};
  SDL_Rect destRect = {x, y, FRAME_WIDTH,
                       FRAME_HEIGHT};  // Modify as needed for position

  SDL_RenderCopy(renderer, sheet->texture, &srcRect, &destRect);
}

void cleanupFrames() {}
