#include "agent_pool.h"

#include <SDL.h>
#include <stdio.h>

#include "agent.h"
#include "clock.h"

#define POOL_SIZE 100

static AgentEntity pool[POOL_SIZE];

void init_agent_pool() {
  for (int i = 0; i < POOL_SIZE; i++) {
    pool[i].agent = (Agent){0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0};  // Initialize with default values
    pool[i].active = 0;
  }
}

int add_agent(float x, float y, AgentType type, AnimationType animation_type,
              ProgressFunction progress, Hitbox* hitbox) {
  int now = get_now();
  for (int i = 0; i < POOL_SIZE; i++) {
    if (!pool[i].active) {
      pool[i].agent =
          (Agent){x, y, type, animation_type, now, now, progress, i, hitbox, 0};
      pool[i].active = 1;
      return i;  // Return the index where the agent was activated
    }
  }
  return -1;  // No available spots
}

void deactivate_agent(int index) {
  if (index >= 0 && index < POOL_SIZE) {
    pool[index].active = 0;
  }
}

void reset_pool() {
  for (int i = 0; i < POOL_SIZE; i++) {
    pool[i].active = 0;
  }
}

AgentEntity* get_pool() { return pool; }

int get_pool_size() { return POOL_SIZE; }
