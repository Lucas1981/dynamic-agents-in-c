#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "SDL_stdinc.h"  // for Uint32

// Forward declaration of Agent
struct Agent;

typedef enum {
  ENEMY_WALKING,
  ENEMY_DYING,
  PLAYER_STANDING,
  PLAYER_WALKING,
  BULLET_ANIMATION,
  NUM_ANIMATIONS  // Always keep this last
} AnimationType;

typedef struct Animation {
  int* frame_indices;  // Array of frame indices
  Uint32 num_frames;   // Number of frames in the animation
} Animation;

void init_animations(void);
void draw_agent(struct Agent* agent);
Animation* get_animation(AnimationType type);
void cleanup_animations(void);

#endif  // ANIMATIONS_H
