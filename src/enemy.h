#ifndef ENEMY_H
#define ENEMY_H

#include "agent.h"  // for Agent, Hitbox

void kill_enemy(Agent *enemy);
void enemy_progress(Agent *enemy);
Hitbox *get_enemy_hitbox(void);

#endif
