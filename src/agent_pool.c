#include "agent_pool.h"

#include <SDL.h>
#include <stdio.h>

#include "agent.h"
#include "clock.h"

#define POOL_SIZE 100

static Agent pool[POOL_SIZE];
static int last_checked_index = 0;

void init_agent_pool(void) {
  for (int i = 0; i < POOL_SIZE; i++) {
    pool[i] = (Agent){0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0};  // Initialize with default values
  }
}

int add_agent(float x, float y, AgentType type, AnimationType animation_type,
              ProgressFunction progress, Hitbox* hitbox) {
  Uint32 now = get_now();
  int added_index;
  int start_index = last_checked_index;
  do {
    if (!pool[last_checked_index].active) {
      pool[last_checked_index] =
          (Agent){x, y, type, animation_type, now, now, progress, hitbox, 0, 1};
      added_index = last_checked_index;
      last_checked_index = (last_checked_index + 1) % POOL_SIZE;
      return added_index;  // Return the index where the agent was activated
    }
    last_checked_index = (last_checked_index + 1) % POOL_SIZE;
  } while (last_checked_index != start_index);
  return -1;  // No available spots
}

void deactivate_agent(Agent* agent) {
  if (agent) {
    agent->active = 0;
  }
}

void reset_pool(void) {
  for (int i = 0; i < POOL_SIZE; i++) {
    pool[i].active = 0;
  }
  last_checked_index = 0;
}

Agent* get_pool(void) { return pool; }

int get_pool_size(void) { return POOL_SIZE; }
