#include "global_state.h"

#include "clock.h"

#define INITIAL_NUMBER_OF_LIVES 3

static GlobalGameState global_game_state;

void increase_level() { global_game_state.level++; }
void decrease_lives() { global_game_state.number_of_lives--; }
void reset_game_state() {
  // Initialize state...
  global_game_state.last_state_change = get_now();
  global_game_state.number_of_lives = INITIAL_NUMBER_OF_LIVES;
  global_game_state.level = 0;
}

void set_game_state(GameState newState) {
  global_game_state.current_state = newState;
}

const GlobalGameState* get_global_game_state() { return &global_game_state; }

void initiate_level(int enemies_target, int enemies_speed,
                    int enemies_spawning_speed) {
  global_game_state.enemies.target = enemies_target;
  global_game_state.enemies.killed = 0;
  global_game_state.enemies.issued = 0;
  global_game_state.enemies.spawning_speed = enemies_spawning_speed;
  global_game_state.enemies.speed = enemies_speed;
}

void change_state(GameState newState) {
  global_game_state.current_state = newState;
  global_game_state.last_state_change = get_now();
}

void increase_enemies_killed() { global_game_state.enemies.killed++; }
void increase_enemies_issued() { global_game_state.enemies.issued++; }