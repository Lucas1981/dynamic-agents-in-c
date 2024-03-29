#include "global_state.h"

#include "clock.h"

#define INITIAL_NUMBER_OF_LIVES 3

static GlobalGameState global_game_state;

void increase_level(void) { global_game_state.level++; }
void decrease_lives(void) { global_game_state.number_of_lives--; }
void reset_game_state(void) {
  // Initialize state...
  global_game_state.last_state_change = get_now();
  global_game_state.number_of_lives = INITIAL_NUMBER_OF_LIVES;
  global_game_state.level = 0;
}

void set_game_state(GameState new_state) {
  global_game_state.current_state = new_state;
}

void initiate_level(int enemies_target, int enemies_speed,
                    Uint32 enemies_spawning_speed) {
  global_game_state.enemies.target = enemies_target;
  global_game_state.enemies.killed = 0;
  global_game_state.enemies.issued = 0;
  global_game_state.enemies.spawning_speed = enemies_spawning_speed;
  global_game_state.enemies.speed = enemies_speed;
}

void change_state(GameState new_state) {
  global_game_state.current_state = new_state;
  global_game_state.last_state_change = get_now();
}

void increase_enemies_killed(void) { global_game_state.enemies.killed++; }
void increase_enemies_issued(void) { global_game_state.enemies.issued++; }
const GlobalGameState* get_global_game_state(void) {
  return &global_game_state;
}
