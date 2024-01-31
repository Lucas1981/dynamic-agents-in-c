#ifndef AGENT_H
#define AGENT_H

#include "SDL_stdinc.h"  // for Uint32
#include "animations.h"  // for AnimationType

typedef enum { PLAYER, ENEMY, BULLET } AgentType;
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
  Hitbox *hitbox;
  int killed;
  int active;
} Agent;

#endif  // AGENT_H
