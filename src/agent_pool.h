#ifndef ENTITY_POOL_H
#define ENTITY_POOL_H

#include "agent.h"       // for Agent, AgentType, Hitbox, ProgressFunction
#include "animations.h"  // for AnimationType

void init_agent_pool(void);
int add_agent(float x, float y, AgentType type, AnimationType animation_type,
              ProgressFunction progress,
              Hitbox* hitbox);  // Find next available spot to activate
void deactivate_agent(Agent* agent);
Agent* get_pool(void);  // New function to get the entire pool
int get_pool_size(void);
void reset_pool(void);

#endif  // ENTITY_POOL_H
