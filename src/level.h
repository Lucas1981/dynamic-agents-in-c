#ifndef LEVEL_H
#define LEVEL_H

#include "SDL_stdinc.h"  // for Uint32

#define FINAL_LEVEL 3

typedef struct {
  int target;                     // Target number of enemies for the level
  int enemies_speed;              // Speed of enemies in this level
  Uint32 enemies_spawning_speed;  // Spawning speed of enemies in this level
} Level;

#endif  // LEVEL_H
