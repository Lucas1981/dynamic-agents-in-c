#include <SDL.h>
#include <stdio.h>

#include "agent.h"
#include "agent_pool.h"
#include "clock.h"
#include "global_state.h"

#define WIDTH 640
#define DYING_TIME 400
#define ENEMY_OFFSET_X 16
#define ENEMY_OFFSET_Y 0
#define ENEMY_WIDTH 32
#define ENEMY_HEIGHT 64

static Uint32 last_time = 0;
static Hitbox enemy_hitbox = {ENEMY_OFFSET_X, ENEMY_OFFSET_Y, ENEMY_WIDTH,
                              ENEMY_HEIGHT};

void kill_enemy(Agent *enemy) {
  enemy->animation_type = ENEMY_DYING;
  enemy->killed = 1;
  enemy->start_time = get_now();
}

void enemy_progress(Agent *enemy) {
  if (enemy->animation_type == ENEMY_DYING) {
    int now = get_now();
    if (now - enemy->start_time > DYING_TIME) {
      deactivate_agent(enemy->index);
    }
    return;
  }

  const GlobalGameState *global_game_state = get_global_game_state();

  Uint32 elapsed_time = get_elapsed_time();
  // Assuming SPEED is defined and elapsed_time is available
  float movement = (float)global_game_state->enemies.speed / 1000.0f *
                   elapsed_time;  // Floating point calculation
  enemy->y += movement;           // Add the movement to enemy->x
}

Hitbox *get_enemy_hitbox(void) { return &enemy_hitbox; }
