#ifndef BULLET_H
#define BULLET_H

#include "agent.h"  // for Agent, Hitbox

void bullet_progress(Agent *enemy);
Hitbox *get_bullet_hitbox(void);

#endif
