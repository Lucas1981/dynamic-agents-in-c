#include "game.h"

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

#include "agent.h"
#include "agent_pool.h"
#include "animations.h"
#include "clock.h"
#include "frames.h"
#include "global_state.h"
#include "graphics.h"
#include "input.h"
#include "level.h"
#include "load_spritesheet.h"
#include "loop.h"
#include "player.h"
#include "screens.h"
#include "sound.h"
#include "sound_queue.h"
#include "user_interface.h"

#define TIME_BETWEEN_STATES 1500

// Variable to hold the current game state
static Spritesheet* sheet;
static Level levels[4] = {
    {10, 150, 1100},  // Level 1: 10 enemies, speed 150, spawn every 1000 ms
    {15, 200, 1000},  // Level 2: 15 enemies, speed 200, spawn every 900 ms
    {20, 250, 900},   // Level 3: 20 enemies, speed 250, spawn every 800 ms
    {25, 300, 800}    // Level 4: 25 enemies, speed 300, spawn every 700 ms
};

// Forward declarations
static void handleTitleState();
static void handleReadyState();
static void handlePlayingState();
static void handleDeadState();
static void handleGameOverState();
static void handleWonState();
static void handleFinishedState();
static void handlePauseState();
static void reset_stage();
static void reset_game();
static void init_game();
static void cleanup_game();
static const int HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2;

void run_game() {
  init_game();

  int gameRunning = 1;
  SDL_Event event;

  srand((unsigned int)time(NULL));

  while (gameRunning) {
    set_time();
    Uint32 now = get_now();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameRunning = 0;
      }
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        gameRunning = 0;
      }
      handle_input(event);
    }

    const GlobalGameState* globalGameState = getGlobalGameState();
    switch (globalGameState->currentState) {
      case TITLE:
        handleTitleState();
        break;
      case READY:
        handleReadyState();
        break;
      case PLAYING:
        handlePlayingState();
        break;
      case DEAD:
        handleDeadState();
        break;
      case GAME_OVER:
        handleGameOverState();
        break;
      case WON:
        handleWonState();
        break;
      case FINISHED:
        handleFinishedState();
        break;
      case PAUSE:
        handlePauseState();
        break;
    }

    render_graphics();
    play_and_empty_queue();
  }

  cleanup_game();
  printf("Goodbye!\n");
}

static void reset_stage() {
  reset_pool();
  const GlobalGameState* global_game_state = getGlobalGameState();
  int level = global_game_state->level;
  addAgent(400.00, 500.00, PLAYER, PLAYER_STANDING, &player_progress, 0);
  initiate_level(levels[level].target, levels[level].enemies_speed,
                 levels[level].enemies_spawning_speed);
  change_state(READY);
}

static void reset_game() {
  reset_game_state();
  reset_stage();
}

static void init_game() {
  printf("Starting initiation.\n");
  // Initialization code here
  if (init_graphics(SCREEN_WIDTH, SCREEN_HEIGHT) != 0) {  // Window size 800x600
    exit(1);
  }
  printf("Graphics done.\n");
  SDL_Renderer* renderer = get_renderer();
  printf("Renderer done.\n");
  sheet = loadSpritesheet("./assets/images/spritesheet.png", renderer, 64, 64);
  printf("Spritesheet done.\n");
  initFrames(sheet);
  printf("Frames done.\n");
  initAnimations();
  printf("Animations done.\n");
  init_sounds();
  init_sound_queue();
  printf("Sound initiation done\n");
  initiate_user_interface();
  printf("User interface initiation done\n");
  initAgentPool();
  printf("Loading screens\n");
  load_screens();
  setGameState(TITLE);
  set_time();
  printf("Initiation complete.\n\n");
}

static void cleanup_game() {
  printf("Cleaning up...\n");
  // Cleanup code here, run in reverse order as initiation
  cleanup_screens();
  cleanup_user_interface();
  cleanup_sound_queue();
  cleanup_sounds();
  cleanupAnimations();
  cleanupFrames();
  freeSpritesheet(sheet);
  cleanup_graphics();
  printf("Cleanup done.\n");
}

static void handleTitleState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  KeyState* keyState = get_key_state();
  if (keyState->enter) {
    reset_game();
  } else {
    draw_screen(TITLE_SCREEN);
    print_user_interface_with_outline("Press enter to start", HALF_SCREEN_WIDTH,
                                      500, TEXT_ALIGN_CENTER);
  }
}

static void handleReadyState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    change_state(PLAYING);
  } else {
    game_loop(0);
    char buffer[64];
    sprintf(buffer, "Level %i", globalGameState->level + 1);
    print_user_interface_with_outline(buffer, HALF_SCREEN_WIDTH, 200,
                                      TEXT_ALIGN_CENTER);
    print_user_interface_with_outline("GET READY!", HALF_SCREEN_WIDTH, 220,
                                      TEXT_ALIGN_CENTER);
  }
}

static void handlePlayingState() { game_loop(1); }

static void handleDeadState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    decrease_lives();
    if (globalGameState->number_of_lives == 0) {
      change_state(GAME_OVER);
    } else {
      reset_stage();
    }
  } else {
    game_loop(0);
    print_user_interface_with_outline("YOU DIED!", HALF_SCREEN_WIDTH, 200,
                                      TEXT_ALIGN_CENTER);
  }
}

static void handleGameOverState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    change_state(TITLE);
  } else {
    print_user_interface_with_outline("GAME OVER", HALF_SCREEN_WIDTH, 200,
                                      TEXT_ALIGN_CENTER);
  }
}

static void handleWonState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    increase_level();
    if (globalGameState->level > FINAL_LEVEL) {
      change_state(FINISHED);
    } else {
      reset_stage();
    }
  } else {
    game_loop(0);
    print_user_interface_with_outline("YOU WON!", HALF_SCREEN_WIDTH, 200,
                                      TEXT_ALIGN_CENTER);
  }
}

static void handleFinishedState() {
  const GlobalGameState* globalGameState = getGlobalGameState();
  Uint32 now = get_now();
  if (now - globalGameState->last_state_change > TIME_BETWEEN_STATES) {
    change_state(TITLE);
  } else {
    print_user_interface_with_outline(
        "YOU FINISHED THE GAME!", HALF_SCREEN_WIDTH, 200, TEXT_ALIGN_CENTER);
  }
}

static void handlePauseState() {
  // Code for PAUSE state
}
