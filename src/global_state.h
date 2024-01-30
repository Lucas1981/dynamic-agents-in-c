#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include <SDL.h>

#define LEFT_BORDER 200
#define RIGHT_BORDER 600
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef enum {
  TITLE,
  READY,
  PLAYING,
  DEAD,
  WON,
  FINISHED,
  GAME_OVER,
} GameState;

typedef struct Enemies {
  int target;
  int issued;
  int killed;
  int speed;
  Uint32 spawning_speed;
} Enemies;

typedef struct {
  GameState current_state;
  Uint32 last_state_change;
  Enemies enemies;
  int number_of_lives;
  int level;
} GlobalGameState;

void reset_game_state(void);
void increase_level(void);
void decrease_lives(void);
void set_game_state(GameState new_state);
void initiate_level(int enemies_target, int enemies_speed,
                    Uint32 enemies_spawning_speed);
void increase_enemies_killed(void);
void increase_enemies_issued(void);
void change_state(GameState new_state);
const GlobalGameState* get_global_game_state(void);

#endif  // GLOBAL_STATE_H
