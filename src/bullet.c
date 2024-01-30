#include <SDL.h>
#include <stdio.h>

#include "agent.h"
#include "agent_pool.h"
#include "clock.h"

#define SPEED 400
#define WIDTH 640
#define LIFESPAN 3000
#define BULLET_OFFSET_X 26
#define BULLET_OFFSET_Y 26
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 10

static Hitbox bullet_hitbox = {BULLET_OFFSET_X, BULLET_OFFSET_Y, BULLET_WIDTH,
                               BULLET_HEIGHT};

Hitbox *get_bullet_hitbox(void) { return &bullet_hitbox; }

void bullet_progress(Agent *bullet) {
  int now = get_now();
  if (now - bullet->creation_time > LIFESPAN) {
    deactivate_agent(bullet->index);
    return;
  }

  Uint32 elapsed_time = get_elapsed_time();
  // Assuming SPEED is defined and elapsed_time is available
  float movement =
      (float)SPEED / 1000.0f * elapsed_time;  // Floating point calculation
  bullet->y -= movement;                      // Add the movement to enemy->x

  // Check if enemy->x is out of bounds and adjust accordingly
  if (bullet->y < 0.0f) {
    bullet->y -= 0.0f;  // Wrap around if it goes over 640
  }
}
