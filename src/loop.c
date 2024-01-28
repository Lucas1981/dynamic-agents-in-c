#include "loop.h"

#include <stdlib.h>

#include "agent.h"
#include "agent_pool.h"
#include "animations.h"
#include "bullet.h"
#include "clock.h"
#include "enemy.h"
#include "global_state.h"
#include "graphics.h"
#include "screens.h"
#include "sound.h"
#include "sound_queue.h"
#include "user_interface.h"

#define ENEMY_LINE_THRESHOLD 600 - 64

static Uint32 enemy_generation_timer = 0;

// Forward declarations
static void attempt_enemy_generation(const GlobalGameState *globalGameState);
static void update_agents();
static void handle_intersection(Agent *source, Agent *target);
static void check_and_handle_collision(AgentEntity *sourceEntity,
                                       AgentEntity *targetEntity);
static void detect_collision();
static void draw_agents();
static void check_stage(const GlobalGameState *global_game_state);
static void handle_user_interface(const GlobalGameState *global_game_state);

void game_loop(int apply_progress) {
  const GlobalGameState *global_game_state = getGlobalGameState();
  draw_screen(LEVEL_SCREEN);
  draw_agents();

  if (apply_progress) {
    attempt_enemy_generation(global_game_state);
    update_agents();
    detect_collision();
    check_stage(global_game_state);
    draw_agents();
    handle_user_interface(global_game_state);
  }
}

static void attempt_enemy_generation(const GlobalGameState *globalGameState) {
  Uint32 now = get_now();

  if (globalGameState->enemies.issued >= globalGameState->enemies.target) {
    return;
  }

  // Check if it is time to add a new agent
  if (enemy_generation_timer == 0 ||
      now - enemy_generation_timer > globalGameState->enemies.spawning_speed) {
    // If so, find a random y coordinate for our new agent
    int x = LEFT_BORDER + rand() % (RIGHT_BORDER - LEFT_BORDER - 64 +
                                    1);  // rand() % 301 gives a range of 0-300

    // Instantiate the agent at the new coordinate
    Hitbox *enemy_hitbox = get_enemy_hitbox();
    addAgent((float)x, 0.0, ENEMY, ENEMY_WALKING, &enemy_progress,
             enemy_hitbox);
    increase_enemies_issued();
    // Reset our timer
    enemy_generation_timer = now;
  }
}

static void update_agents() {
  AgentEntity *pool = get_pool();

  for (int i = 0; i < get_pool_size(); i++) {
    AgentEntity *agentEntity = &pool[i];
    if (agentEntity->active) {
      Agent *agent = &agentEntity->agent;
      agent->progress(agent);
    }
  }
}

static void handle_intersection(Agent *source, Agent *target) {
  kill_enemy(source);
  stage_sound(SCREAM);
  deactivateAgent(target->index);
}

static void check_and_handle_collision(AgentEntity *sourceEntity,
                                       AgentEntity *targetEntity) {
  if (!targetEntity->active || sourceEntity == targetEntity) {
    return;
  }

  Agent *source = &sourceEntity->agent;
  Agent *target = &targetEntity->agent;
  if (target->type != BULLET) {
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

static void detect_collision() {
  AgentEntity *pool = get_pool();
  int pool_size = get_pool_size();

  for (int i = 0; i < pool_size; i++) {
    AgentEntity *sourceEntity = &pool[i];
    if (!sourceEntity->active || sourceEntity->agent.type != ENEMY ||
        // Make sure we don't shoot already dead enemies
        sourceEntity->agent.killed) {
      continue;
    }

    for (int j = 0; j < pool_size; j++) {
      check_and_handle_collision(sourceEntity, &pool[j]);
    }
  }
}

static void draw_agents() {
  AgentEntity *pool = get_pool();

  for (int i = 0; i < get_pool_size(); i++) {
    AgentEntity *agentEntity = &pool[i];
    if (agentEntity->active) {
      Agent *agent = &agentEntity->agent;
      draw(agent);
    }
  }
}

static void check_stage(const GlobalGameState *global_game_state) {
  if (global_game_state->enemies.killed == global_game_state->enemies.target) {
    change_state(WON);
    return;
  }

  // Did any of the enemies cross the line?
  AgentEntity *pool = get_pool();
  for (int i = 0; i < get_pool_size(); i++) {
    AgentEntity *agentEntity = &pool[i];
    if (agentEntity->active) {
      Agent *agent = &agentEntity->agent;
      if (agent->y >= ENEMY_LINE_THRESHOLD) {
        change_state(DEAD);
        return;
      }
    }
  }
}

static void handle_user_interface(const GlobalGameState *global_game_state) {
  char buffer[64];

  sprintf(buffer, "Enemies target = %i", global_game_state->enemies.target);
  print_user_interface_with_outline(buffer, 0, 0, TEXT_ALIGN_LEFT);
  sprintf(buffer, "Enemies killed = %i", global_game_state->enemies.killed);
  print_user_interface_with_outline(buffer, 0, 20, TEXT_ALIGN_LEFT);
  sprintf(buffer, "Lives = %i", global_game_state->number_of_lives);
  print_user_interface_with_outline(buffer, 0, 40, TEXT_ALIGN_LEFT);
  sprintf(buffer, "Level = %i", global_game_state->level + 1);
  print_user_interface_with_outline(buffer, 0, 60, TEXT_ALIGN_LEFT);
}
