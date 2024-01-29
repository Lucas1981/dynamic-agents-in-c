#include "state_handlers.h"

#include "agent.h"
#include "agent_pool.h"
#include "clock.h"
#include "global_state.h"
#include "graphics.h"
#include "input.h"
#include "level.h"
#include "loop.h"
#include "player.h"
#include "screens.h"
#include "user_interface.h"

#define TIME_BETWEEN_STATES 1500

static const int HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2;
static Level levels[4] = {
    {10, 150, 1100},  // Level 1: 10 enemies, speed 150, spawn every 1000 ms
    {15, 200, 1000},  // Level 2: 15 enemies, speed 200, spawn every 900 ms
    {20, 250, 900},   // Level 3: 20 enemies, speed 250, spawn every 800 ms
    {25, 300, 800}    // Level 4: 25 enemies, speed 300, spawn every 700 ms
};

static void reset_stage();
static void reset_game();

void handleTitleState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  KeyState* keyState = get_key_state();
  draw_screen(TITLE_SCREEN);
  print_user_interface_with_outline("Press enter to start", HALF_SCREEN_WIDTH,
                                    500, TEXT_ALIGN_CENTER);
  if (keyState->enter) {
    reset_game();
  }
}

void handleReadyState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  game_loop(0);
  char buffer[64];
  sprintf(buffer, "Level %i", globalGameState->level + 1);
  print_user_interface_with_outline(buffer, HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  print_user_interface_with_outline("GET READY!", HALF_SCREEN_WIDTH, 220,
                                    TEXT_ALIGN_CENTER);
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    change_state(PLAYING);
  }
}

void handlePlayingState() { game_loop(1); }

void handleDeadState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  game_loop(0);
  print_user_interface_with_outline("YOU DIED!", HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    decrease_lives();
    if (globalGameState->number_of_lives == 0) {
      change_state(GAME_OVER);
    } else {
      reset_stage();
    }
  }
}

void handleGameOverState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  print_user_interface_with_outline("GAME OVER", HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    change_state(TITLE);
  }
}

void handleWonState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  game_loop(0);
  print_user_interface_with_outline("YOU WON!", HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    increase_level();
    if (globalGameState->level > FINAL_LEVEL) {
      change_state(FINISHED);
    } else {
      reset_stage();
    }
  }
}

void handleFinishedState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  print_user_interface_with_outline("YOU FINISHED THE GAME!", HALF_SCREEN_WIDTH,
                                    200, TEXT_ALIGN_CENTER);
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    change_state(TITLE);
  }
}

void handlePauseState() {
  // Code for PAUSE state
}

static void reset_stage() {
  reset_pool();
  const GlobalGameState* global_game_state = getGlobalGameState();
  int level = global_game_state->level;
  Hitbox* player_hitbox = get_player_hitbox();
  int half_player_width = player_hitbox->width / 2;
  addAgent(HALF_SCREEN_WIDTH - player_hitbox->x - half_player_width, 500.00,
           PLAYER, PLAYER_STANDING, &player_progress, 0);
  initiate_level(levels[level].target, levels[level].enemies_speed,
                 levels[level].enemies_spawning_speed);
  change_state(READY);
}

static void reset_game() {
  reset_game_state();
  reset_stage();
}