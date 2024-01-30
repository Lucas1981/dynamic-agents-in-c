#include <SDL.h>
#include <stdio.h>

#include "agent.h"
#include "agent_pool.h"
#include "animations.h"
#include "bullet.h"
#include "clock.h"
#include "global_state.h"
#include "input.h"
#include "sound.h"
#include "sound_queue.h"

#define SPEED 350
#define WIDTH 640
#define SHOT_THRESHOLD 300
#define HALF_PLAYER_HEIGHT 32
#define PLAYER_OFFSET_X 16
#define PLAYER_OFFSET_Y 0
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 64

// Uint32 last_time = 0;
static SDL_Event event;
static int last_shot = 0;

static Hitbox player_hitbox = {PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_WIDTH,
                               PLAYER_HEIGHT};

Hitbox *get_player_hitbox(void) { return &player_hitbox; }

void player_progress(Agent *player) {
  Uint32 elapsed_time = get_elapsed_time();
  KeyState *key_state = get_key_state();
  int now = get_now();
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
