#include "loop.h"

#include <SDL.h>
#include <stdlib.h>

#include "agent.h"
#include "agent_pool.h"
#include "bullet.h"
#include "clock.h"
#include "collision.h"
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
static void attempt_enemy_generation(const GlobalGameState *global_game_state);
static void update_agents(void);
static void handle_intersection(Agent *source, Agent *target);
static void check_and_handle_collision(AgentEntity *sourceEntity,
                                       AgentEntity *targetEntity);
static void draw_agents(void);
static void check_stage(const GlobalGameState *global_game_state);
static void handle_user_interface(const GlobalGameState *global_game_state);

void game_loop(int apply_progress) {
  const GlobalGameState *global_game_state = get_global_game_state();
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

static void attempt_enemy_generation(const GlobalGameState *global_game_state) {
  Uint32 now = get_now();

  if (global_game_state->enemies.issued >= global_game_state->enemies.target) {
    return;
  }

  // Check if it is time to add a new agent
  if (enemy_generation_timer == 0 ||
      now - enemy_generation_timer >
          global_game_state->enemies.spawning_speed) {
    // If so, find a random y coordinate for our new agent
    int x = LEFT_BORDER + rand() % (RIGHT_BORDER - LEFT_BORDER - 64 +
                                    1);  // rand() % 301 gives a range of 0-300

    // Instantiate the agent at the new coordinate
    Hitbox *enemy_hitbox = get_enemy_hitbox();
    add_agent((float)x, 0.0, ENEMY, ENEMY_WALKING, &enemy_progress,
              enemy_hitbox);
    increase_enemies_issued();
    // Reset our timer
    enemy_generation_timer = now;
  }
}

static void update_agents(void) {
  AgentEntity *pool = get_pool();

  for (int i = 0; i < get_pool_size(); i++) {
    AgentEntity *agent_entity = &pool[i];
    if (agent_entity->active) {
      Agent *agent = &agent_entity->agent;
      agent->progress(agent);
    }
  }
}

static void draw_agents(void) {
  AgentEntity *pool = get_pool();

  for (int i = 0; i < get_pool_size(); i++) {
    AgentEntity *agent_entity = &pool[i];
    if (agent_entity->active) {
      Agent *agent = &agent_entity->agent;
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
    AgentEntity *agent_entity = &pool[i];
    if (agent_entity->active) {
      Agent *agent = &agent_entity->agent;
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
