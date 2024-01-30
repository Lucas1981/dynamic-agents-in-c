#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "frames.h"

// Forward declaration of Agent
struct Agent;

// Enum for animation types
typedef enum {
  ENEMY_WALKING,
  ENEMY_DYING,
  PLAYER_STANDING,
  PLAYER_WALKING,
  BULLET_ANIMATION,
  NUM_ANIMATIONS  // Always keep this last
} AnimationType;

// Animation structure
typedef struct Animation {
  int* frameIndices;  // Array of frame indices
  int numFrames;      // Number of frames in the animation
} Animation;

// Function to initialize all animations
void init_animations();

void draw(struct Agent* agent);

// Function to get an animation by type
Animation* get_animation(AnimationType type);

// Function to clean up animations
void cleanup_animations();

#endif  // ANIMATIONS_H
