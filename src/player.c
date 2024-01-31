#include "SDL_stdinc.h"    // for Uint32
#include "agent.h"         // for Hitbox, Agent, BULLET
#include "agent_pool.h"    // for add_agent
#include "animations.h"    // for PLAYER_WALKING, AnimationType, BULLET_ANIM...
#include "bullet.h"        // for get_bullet_hitbox, bullet_progress
#include "clock.h"         // for get_elapsed_time, get_now
#include "global_state.h"  // for LEFT_BORDER, RIGHT_BORDER
#include "input.h"         // for get_key_state, KeyState
#include "sound.h"         // for GUNSHOT
#include "sound_queue.h"   // for stage_sound

#define SPEED 350
#define WIDTH 640
#define SHOT_THRESHOLD 300
#define HALF_PLAYER_HEIGHT 32
#define PLAYER_OFFSET_X 16
#define PLAYER_OFFSET_Y 0
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 64

// Uint32 last_time = 0;
static Uint32 last_shot = 0;

static Hitbox player_hitbox = {PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_WIDTH,
                               PLAYER_HEIGHT};

Hitbox *get_player_hitbox(void) { return &player_hitbox; }

void player_progress(Agent *player) {
  Uint32 elapsed_time = get_elapsed_time();
  KeyState *key_state = get_key_state();
  Uint32 now = get_now();
  // Assuming SPEED is defined and elapsed_time is available
  float movement =
      (float)SPEED / 1000.0f * elapsed_time;  // Floating point calculation

  // Update position based on key states
  AnimationType prev_animation_type = player->animation_type;

  player->animation_type = PLAYER_STANDING;

  if (key_state->left) {
    player->x -= movement;
    player->animation_type = PLAYER_WALKING;
  }

  if (key_state->right) {
    player->x += movement;
    player->animation_type = PLAYER_WALKING;
  }

  if (player->animation_type != prev_animation_type) {
    player->start_time = now;
  }

  if (key_state->space &&
      (last_shot == 0 || now - last_shot > SHOT_THRESHOLD)) {
    Hitbox *bullet_hitbox = get_bullet_hitbox();
    add_agent(player->x, player->y - HALF_PLAYER_HEIGHT, BULLET,
              BULLET_ANIMATION, &bullet_progress, bullet_hitbox);
    stage_sound(GUNSHOT);
    last_shot = now;
  }

  if (player->x > RIGHT_BORDER - 64) {
    player->x = RIGHT_BORDER - 64;
  }

  if (player->x < LEFT_BORDER) {
    player->x = LEFT_BORDER;
  }
}
