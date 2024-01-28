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
  PAUSE
} GameState;

typedef struct Enemies {
  int target;
  int issued;
  int killed;
  int speed;
  int spawning_speed;
} Enemies;

typedef struct {
  GameState currentState;
  Uint32 last_state_change;
  Enemies enemies;
  int number_of_lives;
  int level;
} GlobalGameState;

void reset_game_state();
void increase_level();
void decrease_lives();
void setGameState(GameState newState);
void initiate_level(int enemies_target, int enemies_speed,
                    int enemies_spawning_speed);
void increase_enemies_killed();
void increase_enemies_issued();
void change_state(GameState newState);
const GlobalGameState* getGlobalGameState();

#endif  // GLOBAL_STATE_H
