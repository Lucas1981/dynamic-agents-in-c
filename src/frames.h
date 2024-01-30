#ifndef FRAMES_H
#define FRAMES_H

#include "load_spritesheet.h"

// Constant for frame width and height
#define FRAME_WIDTH 64
#define FRAME_HEIGHT 64

// Frame structure
typedef struct Frame {
  int x;
  int y;
} Frame;

Frame* get_frames();

// Function to initialize frames
void init_frames(Spritesheet* spritesheet);

// Function to draw a frame
void draw_frame(int x, int y, Frame* frame);

// Function to clean up frames
void cleanup_frames();

#endif  // FRAMES_H
