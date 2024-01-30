#ifndef LEVEL_H
#define LEVEL_H

#define FINAL_LEVEL 3

typedef struct {
  int target;                     // Target number of enemies for the level
  int enemies_speed;              // Speed of enemies in this level
  Uint32 enemies_spawning_speed;  // Spawning speed of enemies in this level
} Level;

#endif  // LEVEL_H
