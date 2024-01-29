#include "animations.h"

#include <SDL.h>
#include <stdlib.h>

#include "agent.h"
#include "frames.h"

#define FRAME_DURATION 125

// Static array of animations
static Animation animations[NUM_ANIMATIONS];
static Frame* frames;
static Spritesheet* sheet;

static int enemyWalkingFrameIndices[] = {2, 6};
static int playerStandingFrameIndices[] = {0};
static int playerWalkingFrameIndices[] = {4, 0, 5, 0};
static int bulletFrameIndices[] = {7};
static int enemyDyingIndices[] = {1};

void initAnimations() {
  frames = get_frames();

  animations[ENEMY_WALKING].frameIndices = enemyWalkingFrameIndices;
  animations[ENEMY_WALKING].numFrames = 2;

  animations[PLAYER_STANDING].frameIndices = playerStandingFrameIndices;
  animations[PLAYER_STANDING].numFrames = 1;

  animations[PLAYER_WALKING].frameIndices = playerWalkingFrameIndices;
  animations[PLAYER_WALKING].numFrames = 4;

  animations[BULLET_ANIMATION].frameIndices = bulletFrameIndices;
  animations[BULLET_ANIMATION].numFrames = 1;

  animations[ENEMY_DYING].frameIndices = enemyDyingIndices;
  animations[ENEMY_DYING].numFrames = 1;
}

void draw(Agent* agent) {
  Uint32 current_time = SDL_GetTicks();
  Animation animation = animations[agent->animationType];
  Uint32 elapsed_time = current_time - agent->start_time;
  int animationFrameIndex =
      (elapsed_time / FRAME_DURATION) % animation.numFrames;
  int frameIndex = animation.frameIndices[animationFrameIndex];
  Frame frame = frames[frameIndex];
  drawFrame((int)agent->x, (int)agent->y, &frame);
}

Animation* getAnimation(AnimationType type) {
  if (type < 0 || type >= NUM_ANIMATIONS) {
    return NULL;
  }
  return &animations[type];
}

void cleanupAnimations() {
  // Cleanup code here, if necessary.
  // This depends on how frames are allocated and managed.
}
