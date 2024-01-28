#include "agent_pool.h"

#include <SDL.h>
#include <stdio.h>

#include "agent.h"
#include "clock.h"

#define POOL_SIZE 100

static AgentEntity pool[POOL_SIZE];

void initAgentPool() {
  for (int i = 0; i < POOL_SIZE; i++) {
    pool[i].agent = (Agent){0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0};  // Initialize with default values
    pool[i].active = 0;
  }
}

int addAgent(float x, float y, AgentType type, AnimationType animationType,
             ProgressFunction progress, Hitbox* hitbox) {
  int now = get_now();
  for (int i = 0; i < POOL_SIZE; i++) {
    if (!pool[i].active) {
      pool[i].agent =
          (Agent){x, y, type, animationType, now, now, progress, i, hitbox, 0};
      pool[i].active = 1;
      return i;  // Return the index where the agent was activated
    }
  }
  return -1;  // No available spots
}

void deactivateAgent(int index) {
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
