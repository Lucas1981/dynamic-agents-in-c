#ifndef ENTITY_POOL_H
#define ENTITY_POOL_H

#include <SDL.h>

#include "agent.h"

typedef struct AgentEntity {
  Agent agent;
  int active;
} AgentEntity;

void initAgentPool();
int addAgent(float x, float y, AgentType type, AnimationType animationType,
             ProgressFunction progress, Hitbox *hitbox);  // Find next available spot to activate
void deactivateAgent(int index);
AgentEntity* get_pool();  // New function to get the entire pool
int get_pool_size();
void reset_pool();

#endif  // ENTITY_POOL_H
