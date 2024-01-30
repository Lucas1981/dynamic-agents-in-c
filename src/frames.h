#ifndef FRAMES_H
#define FRAMES_H

#include "load_spritesheet.h"

#define FRAME_WIDTH 64
#define FRAME_HEIGHT 64

typedef struct Frame {
  int x;
  int y;
} Frame;

Frame* get_frames(void);
void init_frames(void);
void draw_frame(int x, int y, Frame* frame);
void cleanup_frames(void);

#endif  // FRAMES_H
