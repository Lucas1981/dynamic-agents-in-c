#ifndef AGENT_H
#define AGENT_H

#include <SDL.h>

#include "animations.h"

typedef enum AgentType { PLAYER, ENEMY, BULLET } AgentType;
typedef struct Hitbox {
  int x;
  int y;
  int width;
  int height;
} Hitbox;
typedef void (*ProgressFunction)(struct Agent *);

typedef struct Agent {
  float x;
  float y;
  AgentType type;
  AnimationType animation_type;  // Current animation name
  Uint32 start_time;             // Start time of the animation
  Uint32 creation_time;
  ProgressFunction progress;
  int index;
  Hitbox *hitbox;
  int killed;
} Agent;

#endif  // AGENT_H
