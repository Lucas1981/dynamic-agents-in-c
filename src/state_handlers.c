#include "state_handlers.h"

#include <stdio.h>  // for sprintf

#include "SDL_stdinc.h"      // for Uint32
#include "agent.h"           // for Hitbox, PLAYER
#include "agent_pool.h"      // for add_agent, reset_pool
#include "animations.h"      // for PLAYER_STANDING
#include "clock.h"           // for get_now
#include "global_state.h"    // for change_state, get_global_game_state, Glo...
#include "input.h"           // for get_key_state, KeyState
#include "level.h"           // for FINAL_LEVEL, Level
#include "loop.h"            // for game_loop
#include "player.h"          // for get_player_hitbox, player_progress
#include "screens.h"         // for draw_screen, TITLE_SCREEN
#include "user_interface.h"  // for print_user_interface_with_outline, TEXT_...

#define TIME_BETWEEN_STATES 1500

static const int HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2;
static Level levels[4] = {
    {10, 150, 1100},  // Level 1: 10 enemies, speed 150, spawn every 1000 ms
    {15, 200, 1000},  // Level 2: 15 enemies, speed 200, spawn every 900 ms
    {20, 250, 900},   // Level 3: 20 enemies, speed 250, spawn every 800 ms
    {25, 300, 800}    // Level 4: 25 enemies, speed 300, spawn every 700 ms
};

static void reset_stage(void);
static void reset_game(void);

void handle_title_state(void) {
  KeyState* key_state = get_key_state();
  draw_screen(TITLE_SCREEN);
  print_user_interface_with_outline("Press enter to start", HALF_SCREEN_WIDTH,
                                    500, TEXT_ALIGN_CENTER);
  if (key_state->enter) {
    reset_game();
  }
}

void handle_ready_state(void) {
  const GlobalGameState* global_game_state = get_global_game_state();
  Uint32 now = get_now();
  game_loop(0);
  char buffer[64];
  sprintf(buffer, "Level %i", global_game_state->level + 1);
  print_user_interface_with_outline(buffer, HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  print_user_interface_with_outline("GET READY!", HALF_SCREEN_WIDTH, 220,
                                    TEXT_ALIGN_CENTER);
  if (now - global_game_state->last_state_change > TIME_BETWEEN_STATES) {
    change_state(PLAYING);
  }
}

void handle_playing_state(void) { game_loop(1); }

void handle_dead_state(void) {
  const GlobalGameState* global_game_state = get_global_game_state();
  Uint32 now = get_now();
  game_loop(0);
  print_user_interface_with_outline("YOU DIED!", HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  if (now - global_game_state->last_state_change > TIME_BETWEEN_STATES) {
    decrease_lives();
    if (global_game_state->number_of_lives == 0) {
      change_state(GAME_OVER);
    } else {
      reset_stage();
    }
  }
}

void handle_game_over_state(void) {
  const GlobalGameState* global_game_state = get_global_game_state();
  Uint32 now = get_now();
  print_user_interface_with_outline("GAME OVER", HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  if (now - global_game_state->last_state_change > TIME_BETWEEN_STATES) {
    change_state(TITLE);
  }
}

void handle_won_state(void) {
  const GlobalGameState* global_game_state = get_global_game_state();
  Uint32 now = get_now();
  game_loop(0);
  print_user_interface_with_outline("YOU WON!", HALF_SCREEN_WIDTH, 200,
                                    TEXT_ALIGN_CENTER);
  if (now - global_game_state->last_state_change > TIME_BETWEEN_STATES) {
    increase_level();
    if (global_game_state->level > FINAL_LEVEL) {
      change_state(FINISHED);
    } else {
      reset_stage();
    }
  }
}

void handle_finished_state(void) {
  const GlobalGameState* global_game_state = get_global_game_state();
  Uint32 now = get_now();
  print_user_interface_with_outline("YOU FINISHED THE GAME!", HALF_SCREEN_WIDTH,
                                    200, TEXT_ALIGN_CENTER);
  if (now - global_game_state->last_state_change > TIME_BETWEEN_STATES) {
    change_state(TITLE);
  }
}

static void reset_stage(void) {
  reset_pool();
  const GlobalGameState* global_game_state = get_global_game_state();
  int level = global_game_state->level;
  Hitbox* player_hitbox = get_player_hitbox();
  int half_player_width = player_hitbox->width / 2;
  add_agent(HALF_SCREEN_WIDTH - player_hitbox->x - half_player_width, 500.00,
            PLAYER, PLAYER_STANDING, &player_progress, 0);
  initiate_level(levels[level].target, levels[level].enemies_speed,
                 levels[level].enemies_spawning_speed);
  change_state(READY);
}

static void reset_game(void) {
  reset_game_state();
  reset_stage();
}
