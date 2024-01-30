#include "collision.h"

#include <SDL.h>

#include "agent.h"
#include "agent_pool.h"
#include "enemy.h"
#include "global_state.h"
#include "sound.h"
#include "sound_queue.h"

static void check_and_handle_collision(Agent *source, Agent *target);
static void handle_intersection(Agent *source, Agent *target);

void detect_collision(void) {
  Agent *pool = get_pool();
  int pool_size = get_pool_size();

  for (int i = 0; i < pool_size; i++) {
    Agent *source = &pool[i];
    if (!source->active || source->type != ENEMY ||
        // Make sure we don't shoot already dead enemies
        source->killed) {
      continue;
    }

    for (int j = 0; j < pool_size; j++) {
      check_and_handle_collision(source, &pool[j]);
    }
  }
}

static void check_and_handle_collision(Agent *source, Agent *target) {
  if (!target->active || target->type != BULLET || source == target) {
    return;
  }

  SDL_Rect enemy_box = {source->x + source->hitbox->x,
                        source->y + source->hitbox->y, source->hitbox->width,
                        source->hitbox->height};
  SDL_Rect bullet_box = {target->x + target->hitbox->x,
                         target->y + target->hitbox->y, target->hitbox->width,
                         target->hitbox->height};

  if (SDL_HasIntersection(&enemy_box, &bullet_box)) {
    handle_intersection(source, target);
    increase_enemies_killed();
  }
}

static void handle_intersection(Agent *source, Agent *target) {
  kill_enemy(source);
  stage_sound(SCREAM);
  deactivate_agent(target);
}
