#ifndef ENTITY_POOL_H
#define ENTITY_POOL_H

#include <SDL.h>

#include "agent.h"

typedef struct AgentEntity {
  Agent agent;
  int active;
} AgentEntity;

void init_agent_pool(void);
int add_agent(float x, float y, AgentType type, AnimationType animation_type,
              ProgressFunction progress,
              Hitbox* hitbox);  // Find next available spot to activate
void deactivate_agent(int index);
AgentEntity* get_pool(void);  // New function to get the entire pool
int get_pool_size(void);
void reset_pool(void);

#endif  // ENTITY_POOL_H
