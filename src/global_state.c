#include "global_state.h"

#include "clock.h"

#define INITIAL_NUMBER_OF_LIVES 3

static GlobalGameState globalGameState;

void increase_level() { globalGameState.level++; }
void decrease_lives() { globalGameState.number_of_lives--; }
void reset_game_state() {
  // Initialize state...
  globalGameState.last_state_change = get_now();
  globalGameState.number_of_lives = INITIAL_NUMBER_OF_LIVES;
  globalGameState.level = 0;
}

void setGameState(GameState newState) {
  globalGameState.currentState = newState;
}

const GlobalGameState* getGlobalGameState() { return &globalGameState; }

void initiate_level(int enemies_target, int enemies_speed,
                    int enemies_spawning_speed) {
  globalGameState.enemies.target = enemies_target;
  globalGameState.enemies.killed = 0;
  globalGameState.enemies.issued = 0;
  globalGameState.enemies.spawning_speed = enemies_spawning_speed;
  globalGameState.enemies.speed = enemies_speed;
}

void change_state(GameState newState) {
  globalGameState.currentState = newState;
  globalGameState.last_state_change = get_now();
}

void increase_enemies_killed() { globalGameState.enemies.killed++; }
void increase_enemies_issued() { globalGameState.enemies.issued++; }