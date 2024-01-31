#include "animations.h"

#include <stdlib.h>  // for NULL

#include "SDL_timer.h"  // for SDL_GetTicks
#include "agent.h"      // for Agent
#include "frames.h"     // for Frame, draw_frame, get_frames

#define FRAME_DURATION 125

// Static array of animations
static Animation animations[NUM_ANIMATIONS];
static Frame* frames;

static int enemy_walking_frame_indices[] = {2, 6};
static int player_standing_frame_indices[] = {0};
static int player_walking_frame_indices[] = {4, 0, 5, 0};
static int bullet_frame_indices[] = {7};
static int enemy_dying_indices[] = {1};

void init_animations(void) {
  frames = get_frames();

  animations[ENEMY_WALKING].frame_indices = enemy_walking_frame_indices;
  animations[ENEMY_WALKING].num_frames = 2;

  animations[PLAYER_STANDING].frame_indices = player_standing_frame_indices;
  animations[PLAYER_STANDING].num_frames = 1;

  animations[PLAYER_WALKING].frame_indices = player_walking_frame_indices;
  animations[PLAYER_WALKING].num_frames = 4;

  animations[BULLET_ANIMATION].frame_indices = bullet_frame_indices;
  animations[BULLET_ANIMATION].num_frames = 1;

  animations[ENEMY_DYING].frame_indices = enemy_dying_indices;
  animations[ENEMY_DYING].num_frames = 1;
}

void draw_agent(Agent* agent) {
  Uint32 current_time = SDL_GetTicks();
  Animation animation = animations[agent->animation_type];
  Uint32 elapsed_time = current_time - agent->start_time;
  Uint32 animation_frame_index =
      (elapsed_time / FRAME_DURATION) % animation.num_frames;
  int frame_index = animation.frame_indices[animation_frame_index];
  Frame frame = frames[frame_index];
  draw_frame((int)agent->x, (int)agent->y, &frame);
}

Animation* get_animation(AnimationType type) {
  if (type < 0 || type >= NUM_ANIMATIONS) {
    return NULL;
  }
  return &animations[type];
}

void cleanup_animations(void) {
  // Cleanup code here, if necessary.
  // This depends on how frames are allocated and managed.
}
